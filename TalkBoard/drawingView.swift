//
//  drawingView.swift
//  OpenLive
//
//  Created by 吴方宇 on 2018-12-30.
//  Copyright © 2018 Agora. All rights reserved.
//

import UIKit

class drawningView: UIView {

    
    
    var currentTouch:UITouch?
    var currentPath: Array<CGPoint>?
    
    var currentSNSPath:SNSPath?
    var currentColor:UIColor?
    
   let firebase = SNSFirebase.sharedInstance
    
    var allPaths = Array<SNSPath>()
    var allKeys = Array<String>()
    
    
    required init?(coder aDecoder: NSCoder){
        super.init(coder: aDecoder)
        NotificationCenter.default.addObserver(self, selector: #selector(self.addFromFirebase(sender:)), name: NSNotification.Name(rawValue: firebase.callbbackFromFirebase), object: nil)
        
        NotificationCenter.default.addObserver(self, selector: #selector(drawningView.cleanData(sender:)), name: NSNotification.Name(rawValue: firebase.cleanalldata), object: nil)
    }
    
    
    
    func cleanData(sender: NSNotification){
        print("+++++++++++++++++++++")
        
        allKeys.removeAll()
        allPaths.removeAll()
        firebase.resetValues()
        setNeedsDisplay()
    }
    
    
    
    
func addFromFirebase(sender: NSNotification){
    if let info = sender.userInfo as? Dictionary<String, DataSnapshot>{
        let data2 = info["send"]
        if let firebaseKey = data2?.key{
            if !allKeys.contains(firebaseKey){
                if let data2 = data2?.value{
                    let points = (data2 as AnyObject).value(forKey: "points") as! NSArray
                    let firstPoint = points.firstObject! as! NSObject
                    let currentPoint = CGPoint(x: firstPoint.value(forKey: "x") as! Double,
                                               y: firstPoint.value(forKey: "y") as! Double)
                    currentSNSPath = SNSPath(point: currentPoint, color: UIColor.black)
                    for point in points{
                        let p = CGPoint(x: (point as AnyObject).value(forKey: "x") as! Double,
                                        y: (point as AnyObject).value(forKey: "y") as! Double)
                        currentSNSPath?.addPoint(point: p)
                    }
                }
                resetPatch(SendToFirebase: false)
                setNeedsDisplay()
            }
        }
    }
}
    
    
    //NOTE: Drawing functions
    
    
    override func draw(_ rect: CGRect) {
        super.draw(rect)
        
        let context = UIGraphicsGetCurrentContext()
        context?.setLineWidth(1.5)
        context?.beginPath()
        context?.setStrokeColor(UIColor.black.cgColor)
        

            
        for path in allPaths{
            let pathArray  = path.points
            if let firstPoint = pathArray.first{
                context?.move(to: CGPoint.init(x: firstPoint.x!, y: firstPoint.y!))
                if(pathArray.count > 1){
                    for index in 1...pathArray.count - 1{
                        let currentPoint = pathArray[index]
                        context?.addLine(to: CGPoint.init(x: currentPoint.x!, y: currentPoint.y!))
                    }
                }
                context?.drawPath(using: CGPathDrawingMode.stroke)
            }
        }
        
        
        if let firstPoint = currentPath?.first{
            context?.move(to: firstPoint)
            if(currentPath!.count > 1){
                for index in 1...currentPath!.count - 1{
                    let currentPoint = currentPath![index]
                    context?.addLine(to: currentPoint)
                }
            }
            context?.drawPath(using: CGPathDrawingMode.stroke)
            
        }
    }
    
    
    
    // NOTE: Touch function
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        currentColor = UIColor.black // FIXME;
        if currentPath == nil{
            currentTouch = UITouch()
            currentTouch = touches.first
            let currentPoint = currentTouch?.location(in: self)
            
            if let currentPoint = currentPoint{
                currentPath = Array<CGPoint>()
                currentPath?.append(currentPoint)
                print("Start a new path with point \(currentPoint)")
                
                if let currentColor = currentColor{
                    currentSNSPath = SNSPath(point: currentPoint, color: currentColor)
                }else{
                    currentSNSPath = SNSPath(point: currentPoint, color: UIColor.black)
                }
                
            }else{
                print("Find empty touch")
            }
            
        }
        setNeedsDisplay()
        super.touchesBegan(touches, with: event)
    }
    
    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        addTouch(touches: touches)
        super.touchesMoved(touches, with: event)
    }
    

    
    override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        
        addTouch(touches: touches)
        resetPatch(SendToFirebase: true)
        super.touchesEnded(touches, with: event)
    }
    
    
    override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        resetPatch(SendToFirebase: true)
        print("touch cancel")
        setNeedsDisplay()
        super.touchesCancelled(touches, with: event)
    }
    
    func resetPatch(SendToFirebase: Bool){
        currentTouch = nil
        currentPath = nil
       // currentSNSPath?.serialize()
        if let pathToSend = currentSNSPath{
            if SendToFirebase {
                let returnKey = firebase.addPathToSend(path:pathToSend)
                allKeys.append(returnKey)
            }
            allPaths.append(pathToSend)
        }
    }
    

    func addTouch(touches: Set<UITouch>){
        if currentPath != nil{
            for touch in touches{
                if(currentTouch == touch){
                    let currentPoint = currentTouch?.location(in: self)
                    if let currentPoint = currentPoint{
                        currentPath?.append(currentPoint)
                        currentSNSPath?.addPoint(point: currentPoint)
                        print("End path with point \(currentPoint)")
                    }else{
                        print("Find empty touch")
                    }
                }
            }
        }
        setNeedsDisplay()
    }

    
    

}
