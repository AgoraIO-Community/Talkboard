//
//  MainViewController.swift
//  OpenLive
//
//  Created by GongYuhua on 6/25/16.
//  Copyright © 2016 Agora. All rights reserved.
//

import UIKit
import AgoraRtcEngineKit

class MainViewController: UIViewController {
    
    let firebase = SNSFirebase.sharedInstance
    
    @IBOutlet weak var emailField: UITextField!
    @IBOutlet weak var passwordField: UITextField!
    @IBOutlet weak var signInbutton: UIButton!
    @IBOutlet weak var registerbutton: UIButton!
    
    
    @IBOutlet weak var roomNameTextField: UITextField!
    @IBOutlet weak var popoverSourceView: UIView!
    
    
    fileprivate var videoProfile = AgoraVideoDimension640x360
    
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true);
    }
    
    
    @IBAction func siginIntapped(_ sender: UIButton) {
        if let email = emailField.text, let pass = passwordField.text{
            Auth.auth().signIn(withEmail: email, password: pass) { (user, error) in
                if let u = user {
                    
                    let sheet = UIAlertController(title: nil, message: nil, preferredStyle: .actionSheet)
                    let broadcaster = UIAlertAction(title: "Open Camera Now", style: .default) { [weak self] _ in
                        self?.join(withRole: .broadcaster)
                    }
                    let audience = UIAlertAction(title: "Not Open Camera Now", style: .default) { [weak self] _ in
                        self?.join(withRole: .audience)
                    }
                    let cancel = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
                    sheet.addAction(broadcaster)
                    sheet.addAction(audience)
                    sheet.addAction(cancel)
                    sheet.popoverPresentationController?.sourceView = self.popoverSourceView
                    sheet.popoverPresentationController?.permittedArrowDirections = .up
                    self.present(sheet, animated: true, completion: nil)
                    
                }else{
                }
            }
        }
    }
    
    
    
    
    @IBAction func register(_ sender: UIButton) {
        if let email = emailField.text, let pass = passwordField.text{
            Auth.auth().createUser(withEmail: email, password: pass) { (user, err) in
                if let u = user {
                    self.emailField.text = ""
                    self.passwordField.text = ""
                }else{
                    self.emailField.text = "Error"
                    self.passwordField.text = "Error"
                }
            }
        }
    }
    
    
    
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        guard let segueId = segue.identifier else {
            return
        }
        
        switch segueId {
        case "mainToSettings":
            let settingsVC = segue.destination as! SettingsViewController
            settingsVC.videoProfile = videoProfile
            settingsVC.delegate = self
        case "mainToLive":
            let liveVC = segue.destination as! LiveRoomViewController
            liveVC.roomName = roomNameTextField.text!
            liveVC.videoProfile = videoProfile
            if let value = sender as? NSNumber, let role = AgoraClientRole(rawValue: value.intValue) {
                liveVC.clientRole = role
            }
            liveVC.delegate = self
        default:
            break
        }
    }
}


private extension MainViewController {
    func showRoleSelection() {
        let sheet = UIAlertController(title: nil, message: nil, preferredStyle: .actionSheet)
        let broadcaster = UIAlertAction(title: "Broadcaster", style: .default) { [weak self] _ in
            self?.join(withRole: .broadcaster)
        }
        let audience = UIAlertAction(title: "Audience", style: .default) { [weak self] _ in
            self?.join(withRole: .audience)
        }
        let cancel = UIAlertAction(title: "Cancel", style: .cancel, handler: nil)
        sheet.addAction(broadcaster)
        sheet.addAction(audience)
        sheet.addAction(cancel)
        sheet.popoverPresentationController?.sourceView = popoverSourceView
        sheet.popoverPresentationController?.permittedArrowDirections = .up
        present(sheet, animated: true, completion: nil)
    }
}

private extension MainViewController {
    func join(withRole role: AgoraClientRole) {
        performSegue(withIdentifier: "mainToLive", sender: NSNumber(value: role.rawValue as Int))
    }
}

extension MainViewController: SettingsVCDelegate {
    func settingsVC(_ settingsVC: SettingsViewController, didSelectProfile profile: CGSize) {
        videoProfile = profile
        dismiss(animated: true, completion: nil)
    }
}

extension MainViewController: LiveRoomVCDelegate {
    func liveVCNeedClose(_ liveVC: LiveRoomViewController) {
        let _ = navigationController?.popViewController(animated: true)
    }
}

extension MainViewController: UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        if let string = textField.text , !string.isEmpty {
            showRoleSelection()
        }
        
        return true
    }
}
