//
//  SNSPath.swift
//  OpenLive
//
//  Created by 吴方宇 on 2018-12-30.
//  Copyright © 2018 Agora. All rights reserved.
//

import UIKit

//NOTE: SNSPoints Class
class SNSPoint:NSObject{
    var x:CGFloat?
    var y:CGFloat?
    
    init(point:CGPoint) {
        x = point.x
        y = point.y
        print("New point created")
    }
    
}

//NOTE: SNSPath Class
class SNSPath: NSObject {
    var points:Array<SNSPoint>
    var color: UIColor
    
    init(point:CGPoint, color:UIColor) {
        self.color = color
        self.points = Array<SNSPoint>()
        let newPoint = SNSPoint(point:point)
        points.append(newPoint)
        print("Start track point in SNSPath")
        super.init()
    }
    
    func addPoint(point:CGPoint){
        let newPoint = SNSPoint(point: point)
        points.append(newPoint)
        print("New Point appended")
    }
    
    
    func serialize() -> NSDictionary{
        let dictionary = NSMutableDictionary()
        dictionary["color"] = 1///FIXME
        let pointsofPath = NSMutableArray()
        for point in points{
            let pointDictionary = NSMutableDictionary()
            pointDictionary["x"] = Int(point.x!)
            pointDictionary["y"] = Int(point.y!)
            pointsofPath.add(_:pointDictionary)
        }
        dictionary["points"] = pointsofPath;
        
        print(dictionary)
        return dictionary
    }
    
    
    
    
}
