//
//  SNSFirebase.swift
//  OpenLive
//
//  Created by 吴方宇 on 2018-12-30.
//  Copyright © 2018 Agora. All rights reserved.
//

import UIKit

class SNSFirebase{
    
    
    let callbbackFromFirebase = "callbackFromFirebase"
    
    let cleanalldata = "cleanalldata"
    
    let firebase:DatabaseReference!
    
    static let sharedInstance = SNSFirebase()
    var firebaseHandler = DatabaseHandle()
    
    let pathsInLine = NSMutableSet()
    
    private init(){
        
        FirebaseApp.configure()
        firebase = Database.database().reference(fromURL: "YOUR_REAL_RIME_DATABASE_URL")
        
        firebaseHandler = firebase.observe(.childAdded, with: {(snapshot: DataSnapshot)->Void in
            NotificationCenter.default.post(name: NSNotification.Name(rawValue: self.callbbackFromFirebase), object: nil, userInfo: ["send":snapshot])
        })
        
    }
    
    
    func textUnit(text: String){
        firebase.setValue(text)
    }
    
    func addPathToSend(path:SNSPath)->String{
        
        let firebaseKey = firebase.childByAutoId()
        pathsInLine.add(firebaseKey)
        
        let sendValue = path.serialize()
        
        print("------------\(sendValue)")
        
      
        
        firebaseKey.setValue(sendValue, withCompletionBlock: {
            (error:Error?, ref:DatabaseReference!) in
            if let error = error{
                print("Error saving path to firebase \(error.localizedDescription)")
            }else{
                self.pathsInLine.remove(firebaseKey)
            }
            
        })
        return firebaseKey.key! 
    }
    
    func resetValues(){
        firebase.setValue("")
    }
        
}



