import UIKit

class CleanController: UIViewController {
    
    
    let firebase = SNSFirebase.sharedInstance
    
    
    @IBOutlet weak var clearbutton2: UIButton!
    

    @IBAction func clearbutton3(_ sender: UIButton) {
             NotificationCenter.default.post(name: NSNotification.Name(rawValue: firebase.cleanalldata), object: nil)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
    }
    

}
