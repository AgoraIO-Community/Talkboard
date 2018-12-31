//
//  AgoraRtcEngineKit.h
//  AgoraRtcEngineKit
//
//  Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AgoraConstants.h"
#import "AgoraObjects.h"
#import "AgoraMediaIO.h"

/** Agora provides ensured quality of experience (QoE) for worldwide Internet-based voice and video communications through a virtual global network optimized for real-time web and mobile-to-mobile applications.

 The AgoraRtcEngineKit class is the entry point of the Agora SDK providing API methods for apps to easily start voice and video communication.
 */
@class AgoraRtcEngineKit;

/** The AgoraRtcEngineDelegate protocol enables callback event notifications to your app.

 The SDK uses delegate callback functions in the AgoraRtcEngineDelegate protocol to report runtime events to the app.
 From v1.1, some block callback functions in the SDK are replaced with delegate callback functions. The old block callback functions are therefore deprecated, but can still be used in the current version. However, Agora recommends replacing block callback functions with delegate callback functions. The SDK calls the block callback function if a callback function is defined in both the block and delegate callback functions.
 */
@protocol AgoraRtcEngineDelegate <NSObject>
@optional

#pragma mark Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Delegate Methods

 The SDK uses delegate callback functions in the AgoraRtcEngineDelegate protocol to report runtime events to the app.
 From v1.1, some block callback functions in the SDK are replaced with delegate callback functions. The old block callback functions are therefore deprecated, but can still be used in the current version. However, Agora recommends replacing block callback functions with delegate callback functions. The SDK calls the block callback function if a callback function is defined in both the block and delegate callback functions.
 * -----------------------------------------------------------------------------
 */

#pragma mark Core Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Core Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** A warning has occurred during SDK runtime.

 In most cases, the app can ignore the warning reported by the SDK because the SDK can usually fix the issue and resume running.

 For instance, the SDK may report an AgoraWarningCodeOpenChannelTimeout(106) warning upon disconnection from the server and attempts to reconnect.

 See [AgoraWarningCode](AgoraWarningCode) for details.

 @param engine      AgoraRtcEngineKit object
 @param warningCode Warning code: AgoraWarningCode
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didOccurWarning:(AgoraWarningCode)warningCode;

/** An error occurred during SDK runtime.

   In most cases, reporting an error means that the SDK cannot fix the issue and resume running. The SDK requires the application to take action or in the most basic case, informs the user about the issue.

For example, the SDK reports an AgoraErrorCodeStartCall = 1002 error when failing to initialize a call. The app informs the user that the call initialization failed and invokes the [leaveChannel]([AgoraRtcEngineKit leaveChannel:]) method to leave the channel.

See [AgoraErrorCode](AgoraErrorCode) for details.

 @param engine    AgoraRtcEngineKit object
 @param errorCode AgoraErrorCode
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didOccurError:(AgoraErrorCode)errorCode;

/** The API call was executed successfully.

 @param engine AgoraRtcEngineKit object
 @param error  The error code. If the API call fails, the SDK returns AgoraErrorCode.
 @param api    The API executed by the SDK
 @param result The result of the API call
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didApiCallExecute:(NSInteger)error api:(NSString * _Nonnull)api result:(NSString * _Nonnull)result;

/** The user has successfully joined the specified channel with an assigned channel ID and user ID.

 Same as joinSuccessBlock in the [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) API.

 @param engine  AgoraRtcEngineKit object
 @param channel Channel name
 @param uid     User ID. If the uid is specified in the [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method, it returns the specified ID. If the user ID is not specified when joinChannel is called, the server assigns one automatically.
 @param elapsed Time elapsed (ms) from the user calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didJoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/** A user rejoined the channel.

 If the client loses connection with the server because of network problems, the SDK automatically attempts to reconnect and then triggers this callback function upon reconnection, indicating that the user has rejoined the channel with the assigned channel ID and user ID.

 @param engine  AgoraRtcEngineKit object
 @param channel Channel name
 @param uid     User ID. If the uid is specified in the [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method, it returns the specified ID; if not, it returns an ID that is automatically assigned by the Agora server.
 @param elapsed Time elapsed (ms) from starting to reconnect to successful reconnection.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didRejoinChannel:(NSString * _Nonnull)channel withUid:(NSUInteger)uid elapsed:(NSInteger) elapsed;

/** The user has left the channel.

 When the app calls the [leaveChannel]([AgoraRtcEngineKit leaveChannel:]) method, the SDK uses this callback function to notify the app that the user has successfully left the channel.

 With this callback function, the app retrieves information, such as the call duration and the statistics of the data received/transmitted by [audioQualityOfUid]([AgoraRtcEngineDelegate rtcEngine:audioQualityOfUid:quality:delay:lost:]).

 @param engine AgoraRtcEngineKit object
 @param stats  Statistics of the call: AgoraChannelStats
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLeaveChannelWithStats:(AgoraChannelStats * _Nonnull)stats;

/** The user role in a live broadcast has switched. For example, from a host to an audience or vice versa.

 @param engine  AgoraRtcEngineKit object.
 @param oldRole Role that the user switched from: AgoraClientRole.
 @param newRole Role that the user switched to: AgoraClientRole.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didClientRoleChanged:(AgoraClientRole)oldRole newRole:(AgoraClientRole)newRole;

/** The user/host has joined the channel. Same as [userJoinedBlock]([AgoraRtcEngineKit userJoinedBlock:]).

 - Communication mode: This callback function notifies the application that another user has joined the channel. If there are other users in the channel when that user joins, the SDK also reports to the application on the existing users who are already in the channel.
 - Live-broadcast mode: This callback function notifies the application that the host has joined the channel. If other hosts are already in the channel, the SDK also reports to the application on the existing hosts who are already in the channel. Agora recommends limiting the number of hosts to 17.

 Note: In the live broadcast scenario:

 * The host receives the callback when another host joins the channel.
 * The audience in the channel receives the callback when a new host joins the channel.
 * When a web application joins the channel, this callback function is triggered as long as the web application publishes streams.

 @param engine  AgoraRtcEngineKit object.
 @param uid     User ID of the user/host. If the uid is specified in the [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method, the specified ID is returned; if not, an ID automatically assigned by the Agora server is returned.
 @param elapsed Time elapsed (ms) from the newly joined user/host calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) or [setClientRole]([AgoraRtcEngineKit setClientRole:]) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didJoinedOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;

/** A user has left the channel or gone offline. Same as [userOfflineBlock]([AgoraRtcEngineKit userOfflineBlock:]).

 The SDK reads the timeout data to determine if a user has left the channel (or has gone offline). If no data package is received from the user within 15 seconds, the SDK assumes the user is offline. A poor network connection may lead to false detections, so use signaling for reliable offline detection.

 Note: In the live broadcast scenario:

 * The host can receive the callback when another host joins the channel.
 * All the audience in the channel can receive the callback when the new host joins the channel.
 * When a web application joins the channel, this callback function is triggered as long as the web application publishes streams.

 @param engine AgoraRtcEngineKit object
 @param uid    User ID. If the uid is specified in the [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) method, returns the specified ID. If the uid is not specified in the joinChannelByToken method, it will be automatically assigned by the Agora server.
 @param reason Reason why the user has gone offline: AgoraUserOfflineReason
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didOfflineOfUid:(NSUInteger)uid reason:(AgoraUserOfflineReason)reason;

/** The last mile network quality of the local user.

 This callback function is triggered once every two seconds after [enableLastmileTest]([AgoraRtcEngineKit enableLastmileTest]) is called.

 @param engine  AgoraRtcEngineKit object
 @param quality Network quality: AgoraNetworkQuality
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine lastmileQuality:(AgoraNetworkQuality)quality;

/** The connection between the SDK and the server has been interrupted.

Once the connection is lost, the SDK attempts to reconnect until the
   application calls [leaveChannel]([AgoraRtcEngineKit leaveChannel:]).

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineConnectionDidInterrupted:(AgoraRtcEngineKit * _Nonnull)engine;

/** The connection between the SDK and the server is lost.

 The [rtcEngineConnectionDidInterrupted]([AgoraRtcEngineDelegate rtcEngineConnectionDidInterrupted:]) callback function is triggered and the SDK attempts to reconnect automatically.
 If the reconnection fails within a certain period (10 seconds by default), the  [rtcEngineConnectionDidLost]([AgoraRtcEngineDelegate rtcEngineConnectionDidLost:]) callback function is triggered. The SDK attempts to reconnect until the app calls [leaveChannel]([AgoraRtcEngineKit leaveChannel:]).

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineConnectionDidLost:(AgoraRtcEngineKit * _Nonnull)engine;

/** Your connection has been banned by the Agora Server.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineConnectionDidBanned:(AgoraRtcEngineKit * _Nonnull)engine;

/** The Token will expire in 30 seconds.

 If the Token specified when calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) expires, the user will become offline. This callback function is triggered 30 seconds before the Token expires to remind the app to renew the Token.
 Upon receiving this callback function, generate a new Token on the server and call [renewToken]([AgoraRtcEngineKit renewToken:]) to pass the new Token on to the SDK.

 @param engine AgoraRtcEngineKit object.
 @param token  The Token that will expire in 30 seconds.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine tokenPrivilegeWillExpire:(NSString *_Nonnull)token;

/** The Token has expired.

 After a Token is specified by calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]), if the SDK losses connection with the Agora server due to network issues, the Token may expire after a certain period of time and a new Token may be required to reconnect to the server.

 This callback function notifies the application to generate a new Token. Call [renewToken]([AgoraRtcEngineKit renewToken:]) to renew the Token.

In previous SDKs, this function was provided in the [didOccurError]([AgoraRtcEngineDelegate rtcEngine:didOccurError:]) callback function, the AgoraErrorCodeTokenExpired(-109),
 AgoraErrorCodeInvalidToken(-110) errors. Starting from v1.7.3, the old method is still valid, but it is recommended to use this callback function.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineRequestToken:(AgoraRtcEngineKit * _Nonnull)engine;


#pragma mark Media Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Media Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The state of the microphone has changed.

 @param enabled  * YES: The microphone is enabled.
 * NO: The microphone is disabled.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didMicrophoneEnabled:(BOOL)enabled;

/** Indicates who is talking and the speaker's volume.

 Same as [audioVolumeIndicationBlock]([AgoraRtcEngineKit audioVolumeIndicationBlock:]).

 This callback function is disabled by default and can be enabled by the [enableAudioVolumeIndication]([AgoraRtcEngineKit enableAudioVolumeIndication:smooth:]) method.

 In the returned speaker's array:

 * If the uid is 0 (the local user is the speaker), the returned volume is the totalVolume.
 * If the uid is not 0 and the volume is 0, the specified user did not speak.
 * If a uid is found in the previous speaker's array but not in the current speaker's array, the specified user did not speak.

 @param engine      AgoraRtcEngineKit object.
 @param speakers    An array containing the user ID and volume information for each speaker: AgoraRtcAudioVolumeInfo

- uid: User ID of the speaker.
- volume：Volume of the speaker. The value ranges between 0 (lowest volume) and 255 (highest volume).

 @param totalVolume Total volume after audio mixing. The value ranges between 0 (lowest volume) and 255 (highest volume).
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine reportAudioVolumeIndicationOfSpeakers:(NSArray<AgoraRtcAudioVolumeInfo *> * _Nonnull)speakers totalVolume:(NSInteger)totalVolume;

/** The user who is speaking in the channel.

If the user has enabled the audio volume indication by calling [enableAudioVolumeIndication](enableAudioVolumeIndication:smooth:), this callback function returns the user ID of the active speaker whose voice is detected by the audio volume detection module of the SDK.

Note:

* To receive this callback function, you need to call [enableAudioVolumeIndication](enableAudioVolumeIndication:smooth:).
* This callback function returns the user ID of the user whose voice volume is the highest during a period of time, instead of at an instant.
 @param engine     AgoraRtcEngineKit object.
 @param speakerUid The user ID of the active speaker. A speakerUid of 0 represents the local user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine activeSpeaker:(NSUInteger)speakerUid;

/** The first audio frame has been received by the local user.

 @param engine  AgoraRtcEngineKit object
 @param elapsed Time elapsed (ms) from the local user calling [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine firstLocalAudioFrame:(NSInteger)elapsed;

/**  The first audio frame has been received by the specified remote user.

 @param engine  AgoraRtcEngineKit object.
 @param uid     User ID of the remote user.
 @param elapsed Time elapsed (ms) from the remote user calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine firstRemoteAudioFrameOfUid:(NSUInteger)uid elapsed:(NSInteger)elapsed;

/** The video playback stopped.

 The app can use this callback function to change the configuration of the view (for example, displaying other pictures in the view) after the video stops.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineVideoDidStop:(AgoraRtcEngineKit * _Nonnull)engine;

 /** The first local frame is rendered on the video window.

 Same as [firstLocalVideoFrameBlock]([AgoraRtcEngineKit firstLocalVideoFrameBlock:]).
 @param engine  AgoraRtcEngineKit object.
 @param size    Size of the video (width and height).
 @param elapsed Time elapsed (ms) from the local user calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback function is triggered.

 If [startPreview]([AgoraRtcEngineKit startPreview]) is called before [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]), then this is the time elapsed from [startPreview]([AgoraRtcEngineKit startPreview]) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine firstLocalVideoFrameWithSize:(CGSize)size elapsed:(NSInteger)elapsed;

/** The first frame of the remote user has been decoded successfully. Same as [firstRemoteVideoDecodedBlock]([AgoraRtcEngineKit firstRemoteVideoDecodedBlock:]).

 @param engine  AgoraRtcEngineKit object.
 @param uid     Remote user ID.
 @param size    Size of the video (width and height).
 @param elapsed Time elapsed (ms) from the remote user calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine firstRemoteVideoDecodedOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/** The first remote video frame has been received and rendered. Same as [firstRemoteVideoFrameBlock]([AgoraRtcEngineKit firstRemoteVideoFrameBlock:]).

 @param engine  AgoraRtcEngineKit object.
 @param uid     User ID of the remote user sending the video stream.
 @param size    Size of the video (width and height).
 @param elapsed Time elapsed (ms) from the remote user calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]) until this callback function is triggered.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine firstRemoteVideoFrameOfUid:(NSUInteger)uid size:(CGSize)size elapsed:(NSInteger)elapsed;

/** A remote user's audio was muted or unmuted.

 @param engine AgoraRtcEngineKit object
 @param muted  Whether the remote user's audio stream has been muted or unmuted: * YES: The user's audio stream has been muted.
 * NO: The user's audio stream has been unmuted.
 @param uid    Remote user ID
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didAudioMuted:(BOOL)muted byUid:(NSUInteger)uid;

/** A remote user's video has paused or resumed. Same as [userMuteVideoBlock]([AgoraRtcEngineKit userMuteVideoBlock:]).

 Note:  Invalid when the number of users in a channel exceeds 20.

 @param engine AgoraRtcEngineKit object.
 @param muted  A remote user's video has paused or resumed:

 * YES: Paused.
 * NO: Resumed.

 @param uid    ID of the remote user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didVideoMuted:(BOOL)muted byUid:(NSUInteger)uid;

/** Enables/disables the video function of a specified user.

 Disabling the video function means that the specified user is only in a voice call, and can neither render/send any video nor receive/display any video from other users.

 @param engine  AgoraRtcEngineKit object.
 @param enabled Enable or disable the video of a specified user:

 * YES: Enable. The specified user is in a video call.
 * NO: Disable. The specified user is only in a voice call, where the user can neither send or receive any video stream.

 @param uid  ID of the specified user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didVideoEnabled:(BOOL)enabled byUid:(NSUInteger)uid;

/** Enables/disables the local video function of a specified user.

This method is only applicable to the scenario when the specified user only wants to watch the remote video without sending any video stream to the other user.

 @param engine  AgoraRtcEngineKit object.
 @param enabled Enable or disable the local video function of a specified user:

 * YES: Enabled. Other users in the channel can see the video of the specified user.
 * NO: Disabled. Other users in the channel do not receive the video stream from the specified user, while the specified user can still receive the video streams from other users.

 @param uid  ID of the specified user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLocalVideoEnabled:(BOOL)enabled byUid:(NSUInteger)uid;

/** The video size or rotation of a specified remote user has changed.

 @param engine   AgoraRtcEngineKit object
 @param uid      User ID of the remote user or local user (0) whose video size or rotation has changed
 @param size     New video size
 @param rotation New rotation of the video (0 to 360)
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine videoSizeChangedOfUid:(NSUInteger)uid size:(CGSize)size rotation:(NSInteger)rotation;

/** The remote video stream state has changed.

 @param engine AgoraRtcEngineKit object
 @param uid    ID of the user whose video state has changed.
 @param state  State of the remote video: Stopped playing, playing normally, or frozen. See AgoraVideoRemoteState for details.

 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSUInteger)uid state:(AgoraVideoRemoteState)state;


#pragma mark Fallback Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Fallback Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The locally published media stream fell back to an audio-only stream due to poor network conditions or switched back to the video when the network conditions improved.

 If you call [setLocalPublishFallbackOption]([AgoraRtcEngineKit setLocalPublishFallbackOption:]) and set option as AgoraStreamFallbackOptionAudioOnly, this callback function will be triggered when the locally published stream falls back to audio-only mode due to poor uplink conditions, or when the audio stream switches back to the video when the uplink network condition improves.

 Note: Once the locally published stream falls back to audio only, the remote app will receive the [userMuteVideoBlock]([AgoraRtcEngineKit userMuteVideoBlock:]) callback function.

 @param engine              AgoraRtcEngineKit object.
 @param isFallbackOrRecover * YES: The locally published stream fell back to audio-only due to poor network conditions.
 * NO: The locally published stream switched back to the video, after the network conditions improved.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didLocalPublishFallbackToAudioOnly:(BOOL)isFallbackOrRecover;

 /** The remotely subscribed media stream fell back to an audio-only stream due to poor network conditions or switched back to the video after the network conditions improved.

 If you set the fallback option to AgoraStreamFallbackOptionAudioOnly in [setRemoteSubscribeFallbackOption]([AgoraRtcEngineKit setRemoteSubscribeFallbackOption:]),
 this method will be triggered when the remote stream falls back to audio only due to poor network conditions or switches back to the video after the network condition improves.

 Note: Once the remotely subscribed stream is switched to the low stream due to poor network conditions, you can monitor the stream switch between a high and low stream in the [remoteVideoStats]([AgoraRtcEngineDelegate rtcEngine:remoteVideoStats:]) callback function.

 @param engine              AgoraRtcEngineKit object.
 @param isFallbackOrRecover * YES: The remotely subscribed stream fell back to audio-only due to poor network conditions.
 * NO: The remotely subscribed stream switched back to the video stream after the network conditions improved.
 @param uid                 Remote user ID
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didRemoteSubscribeFallbackToAudioOnly:(BOOL)isFallbackOrRecover byUid:(NSUInteger)uid;


#pragma mark Device Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Device Delegate Methods
 * -----------------------------------------------------------------------------
 */

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))

/** The specified device state.

 Note: This method applies to macOS only.

 @param engine     AgoraRtcEngineKit object
 @param deviceId   Device ID
 @param deviceType AgoraMediaDeviceType
 @param state      State of the device:

 * 0: Added.
 * 1: Removed.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine device:(NSString * _Nonnull)deviceId type:(AgoraMediaDeviceType)deviceType stateChanged:(NSInteger) state;

#endif

/** The local audio route changed.

 @param engine  AgoraRtcEngineKit object
 @param routing Audio route: AgoraAudioOutputRouting
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didAudioRouteChanged:(AgoraAudioOutputRouting)routing;

/** The camera is turned on and is ready to capture the video.

 Same as [cameraReadyBlock]([AgoraRtcEngineKit cameraReadyBlock:]).

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineCameraDidReady:(AgoraRtcEngineKit * _Nonnull)engine;

#if TARGET_OS_IPHONE

/** A camera focus position changed.

 Note: This method only applies to iOS.

 This callback function indicates the camera's focus position has changed.

 @param engine AgoraRtcEngineKit object
 @param rect   Focus rectangle in the local preview
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine cameraFocusDidChangedToRect:(CGRect)rect;
#endif


#pragma mark Statistics Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Statistics Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The audio quality of the current call is reported once every two seconds. Same as [audioQualityBlock]([AgoraRtcEngineKit audioQualityBlock:]).

 @param engine  AgoraRtcEngineKit object.
 @param uid     User ID of the speaker.
 @param quality Audio quality of the user: AgoraNetworkQuality
 @param delay   Time delay (ms).
 @param lost    Audio packet loss rate (%).
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine audioQualityOfUid:(NSUInteger)uid quality:(AgoraNetworkQuality)quality delay:(NSUInteger)delay lost:(NSUInteger)lost;

/** The statistics of the current call session is reported once every two seconds.

 Same as [rtcStatsBlock]([AgoraRtcEngineKit rtcStatsBlock:])

 @param engine AgoraRtcEngineKit object
 @param stats  RTC engine statistics: [AgoraChannelStats](AgoraChannelStats).
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine reportRtcStats:(AgoraChannelStats * _Nonnull)stats;

/** The network quality of each user in a communication or live broadcast channel.

 This callback is triggered once every two seconds to report the uplink and downlink network conditions of each user in the channel.

 @param engine    AgoraRtcEngineKit object
 @param uid       User ID. The network quality of the user with this uid is reported. If uid is 0, the local network quality is reported.
 @param txQuality Transmission quality of the user: AgoraNetworkQuality.
 @param rxQuality Receiving quality of the user: AgoraNetworkQuality.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine networkQuality:(NSUInteger)uid txQuality:(AgoraNetworkQuality)txQuality rxQuality:(AgoraNetworkQuality)rxQuality;

/** The statistics of the uploading local video streams.

 Same as [localVideoStatBlock]([AgoraRtcEngineKit localVideoStatBlock:]). This method reports the statistics of the local video streams once every two seconds.

 @param engine AgoraRtcEngineKit object.
 @param stats  Statistics of the uploading local video streams: AgoraRtcLocalVideoStats
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine localVideoStats:(AgoraRtcLocalVideoStats * _Nonnull)stats;

/** The statistics of the receiving remote video streams.

The SDK updates the application on the statistics of receiving remote video streams for each user/host once every 2 seconds.

If there are multiple remote users/hosts, this callback is triggered multiple times every 2 seconds.

 @param engine AgoraRtcEngineKit object
 @param stats  Statistics of the receiving remote video streams: AgoraRtcRemoteVideoStats
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine remoteVideoStats:(AgoraRtcRemoteVideoStats * _Nonnull)stats;

/** The remote audio transport statistics.

 This callback function is triggered every two seconds after the user receives the audio data packet sent from a remote user.

 @param engine     AgoraRtcEngineKit object.
 @param uid        User ID of the remote user sending the audio data packet.
 @param delay      Time delay (ms) from the remote user to the local client.
 @param lost       Packet loss rate (%).
 @param rxKBitRate Received audio bitrate (Kbps) of the packet from the remote user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine audioTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate;

/** The remote video transport statistics.

 This callback function is triggered every two seconds after the user receives the video data packet sent from a remote user.

 @param engine     AgoraRtcEngineKit object.
 @param uid        User ID of the remote user sending the video packet.
 @param delay      Time delay (ms) from the remote user to the local client.
 @param lost       Packet loss rate (%).
 @param rxKBitRate Received video bitrate (Kbps) of the packet from the remote user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine videoTransportStatsOfUid:(NSUInteger)uid delay:(NSUInteger)delay lost:(NSUInteger)lost rxKBitRate:(NSUInteger)rxKBitRate;


#pragma mark Audio Player Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Audio Player Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The audio mixing file playback stopped after calling [startAudioMixing]([AgoraRtcEngineKit startAudioMixing:loopback:replace:cycle:]).

 If you failed to call [startAudioMixing]([AgoraRtcEngineKit startAudioMixing:loopback:replace:cycle:]), it returns the warning code AgoraWarningCodeAudioMixingOpenError in the [didOccurWarning]([AgoraRtcEngineDelegate rtcEngine:didOccurWarning:]) callback function.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineLocalAudioMixingDidFinish:(AgoraRtcEngineKit * _Nonnull)engine;

/** The remote user started audio mixing.

When a remote user calls [startAudioMixing]([AgoraRtcEngineKit startAudioMixing:loopback:replace:cycle:]), this callback function will be triggered.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineRemoteAudioMixingDidStart:(AgoraRtcEngineKit * _Nonnull)engine;

/** The remote user ended audio mixing.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineRemoteAudioMixingDidFinish:(AgoraRtcEngineKit * _Nonnull)engine;

/** A specified sound effect playback stopped.

 This callback function is triggered when the audio effect file playback is finished after calling [playEffect]([AgoraRtcEngineKit playEffect:filePath:loopCount:pitch:pan:gain:publish:]).

 @param engine  AgoraRtcEngineKit object.
 @param soundId ID of the sound effect. Each sound effect has a unique ID.
 */
- (void)rtcEngineDidAudioEffectFinish:(AgoraRtcEngineKit * _Nonnull)engine soundId:(NSInteger)soundId;


#pragma mark CDN Publisher Delegate Methods

/**-----------------------------------------------------------------------------
 * @name CDN Publisher Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The status of publishing a stream in CDN live.

 @param engine    AgoraRtcEngineKit object.
 @param url       Address to which the publisher publishes the stream.
 @param errorCode [AgoraErrorCode](AgoraErrorCode). Main errors include:

 - AgoraErrorCodeTimedOut(10): The publishing has timed out.
 - AgoraErrorCodeAlreadyInUse(19): The chosen HTTP/HTTPS address is already in use for CDN live streaming.
 - AgoraErrorCodeResourceLimited(22): The system does not have enough resource for the CDN live streaming.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine streamPublishedWithUrl:(NSString * _Nonnull)url errorCode:(AgoraErrorCode)errorCode;

/** A stream was unpublished.

 @param engine AgoraRtcEngineKit object.
 @param url    HTTP/HTTPS address to which the publisher unpublishes the stream.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine streamUnpublishedWithUrl:(NSString * _Nonnull)url;

/** The publisher's transcoding was updated.

 @param engine AgoraRtcEngineKit object.
 */
- (void)rtcEngineTranscodingUpdated:(AgoraRtcEngineKit * _Nonnull)engine;


#pragma mark Inject Stream URL Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Inject Stream URL Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The status of the externally injected video stream.

@param engine  AgoraRtcEngineKit object.
@param url     HTTP/HTTPS address of the externally injected video stream.
@param uid     User ID
@param status  Status of the externally injected video stream: AgoraInjectStreamStatus
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine streamInjectedStatusOfUrl:(NSString * _Nonnull)url uid:(NSUInteger)uid status:(AgoraInjectStreamStatus)status;

#pragma mark Stream Message Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Stream Message Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The local user has received the data stream from the remote user within five seconds.

 @param engine   AgoraRtcEngineKit object.
 @param uid      User ID of the remote user sending the message.
 @param streamId Stream ID.
 @param data     Data received by the local user.
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine receiveStreamMessageFromUid:(NSUInteger)uid streamId:(NSInteger)streamId data:(NSData * _Nonnull)data;

/** The local user has not received the data stream from the remote user within five seconds.

 @param engine   AgoraRtcEngineKit object
 @param uid      User ID of the remote user sending the message.
 @param streamId Stream ID
 @param error    AgoraErrorCode
 @param missed Number of lost messages
 @param cached Number of incoming cached messages when the data stream is interrupted
 */
- (void)rtcEngine:(AgoraRtcEngineKit * _Nonnull)engine didOccurStreamMessageErrorFromUid:(NSUInteger)uid streamId:(NSInteger)streamId error:(NSInteger)error missed:(NSInteger)missed cached:(NSInteger)cached;


#pragma mark Miscellaneous Delegate Methods

/**-----------------------------------------------------------------------------
 * @name Miscellaneous Delegate Methods
 * -----------------------------------------------------------------------------
 */

/** The media engine has loaded successfully.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineMediaEngineDidLoaded:(AgoraRtcEngineKit * _Nonnull)engine;

/** The media engine has started successfully.

 @param engine AgoraRtcEngineKit object
 */
- (void)rtcEngineMediaEngineDidStartCall:(AgoraRtcEngineKit * _Nonnull)engine;
@end

#pragma mark - AgoraRtcEngineKit

/** Provides all methods invoked by your app.

 Agora provides ensured quality of experience (QoE) for worldwide Internet-based voice and video communications through a virtual global network optimized for real-time web and mobile-to-mobile apps.

 AgoraRtcEngineKit is the basic interface class of Agora SDK. Creating an AgoraRtcEngineKit object and then calling the methods of this object enables the use of Agora SDK’s communication functionality.
*/
__attribute__((visibility("default"))) @interface AgoraRtcEngineKit : NSObject

#pragma mark Core Service

/**-----------------------------------------------------------------------------
 * @name Core Service
 * -----------------------------------------------------------------------------
 */

/** Sets and retrieves the SDK delegate */
@property (nonatomic, weak) id<AgoraRtcEngineDelegate> _Nullable delegate;

/** Initializes the AgoraRtcEngineKit object.

 Call this method to initialize the service before using AgoraRtcEngineKit.
 The SDK uses the delegate to inform the app on engine runtime events. All methods defined in the delegate are optional implementation methods.
 @warning Only users with the same App ID can call each other.
 @param appId    App ID issued to the application developers by Agora. Apply for a new one from Agora if the key is missing in your kit. Each project will be assigned a unique App ID. The App ID identifies your project and organization in the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) method to access the Agora Global Network, and enable one-to-one or one-to-more communication or live-broadcast sessions using a unique channel name for your App ID.
 @param delegate AgoraRtcEngineDelegate

 @return An object of the AgoraRtcEngineKit class.
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<AgoraRtcEngineDelegate> _Nullable)delegate;

/** Destroys the RtcEngine Instance

 This method releases all the resources used by the Agora SDK. This is useful for apps occasionally making voice or video calls, to free up resources for other operations when not making calls.
 Once the app has called this method to release the created RtcEngine instance, no other methods in the SDK can be used and no callback functions occur. To start communications again, initialize [sharedEngineWithappId](sharedEngineWithAppId:delegate:) to establish a new AgoraRtcEngineKit instance.

 Note:

 - Use this method in the subthread.
 - This method is called synchronously. The result returns after the AgoraRtcEngineKit object resources are released. The app should not call this interface in the callback function generated by the SDK, otherwise, the SDK must wait for the callback to return before it can reclaim the related object resources, causing a deadlock.
 */
+ (void)destroy;

/** Enables interoperability with the Agora Web SDK.

 @param enabled Whether interoperability with the Agora Web SDK is enabled:

 * YES: Enabled.
 * NO: Disabled.

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableWebSdkInteroperability:(BOOL)enabled;

/** Sets the channel profile.

The SDK needs to know the application scenario in order to set the appropriate channel profile to apply different optimization methods.

The Agora Native SDK supports the following channel profiles:

- Communication
- Live Broadcast
- Gaming (for the Agora Gaming SDK only)

Note:

* Only one profile can be used at the same time within the same channel. To switch to another profile, use [destroy](destroy) to destroy the current Engine and create a new one using [sharedEngineWithAppId](AgoraRtcEngine sharedEngineWithAppId) before calling this method to set the new channel profile.
* Ensure different App IDs are used for different channel profiles.
* This method must be called and configured before a user [joins a channel](joinChannelByToken:channelId:info:uid:joinSuccess:) because the channel profile cannot be configured when the channel is in use.
* In the communication mode, the Agora SDK supports encoding only in raw data, not in texture.

 @param profile Channel profile: [AgoraChannelProfile](AgoraChannelProfile).

 @return * 0: Success. * < 0: Failure.
 */
- (int)setChannelProfile:(AgoraChannelProfile)profile;

/** Sets the role of the user, such as a host or an audience (default), before joining a channel.

This method can be used to switch the user role after the user joins a channel.

 @param role Role of the client: AgoraClientRole.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setClientRole:(AgoraClientRole)role;

/** Allows a user to join a channel.

Users in the same channel can talk to each other, and multiple users in the same channel can start a group chat. Users with different App IDs cannot call each other even if they join the same channel.

Once in a call, the user must call the [leaveChannel](leaveChannel:) method to exit the current call, prior to entering another channel. This method is called asynchronously; therefore, it can be called in the main user interface thread.

 The SDK uses the OS X’s AVAudioSession shared object for audio recording and playing, so using this object may affect the SDK’s audio functions.
 Once this method is called successfully, the SDK will trigger the callback. If both joinSuccessBlock and [didJoinChannel]([AgoraRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]) are implemented, the priority of joinSuccessBlock is higher than [didJoinChannel]([AgoraRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]), thus [didJoinChannel]([AgoraRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]) will be ignored. If you want to use [didJoinChannel]([AgoraRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]), set joinSuccessBlock as nil.

 Note: A channel does not accept duplicate uids, such as two users with the same uid. If you set uid as 0, the system will automatically assign a uid.

 @param token A Token generated by the app server. In most circumstances, the static App ID will suffice. For added security, use a Token.

 * This parameter is optional if the user uses a static App ID. In this case, pass nil as the parameter value.
 * If the user uses a Token, Agora issues an additional App Certificate to the application developers. Developers can then generate a user key with the algorithm and App Certificate provided by Agora for user authentication on the server.
 * Ensure that the App ID you use for creating the Token is exactly the same one used by [sharedEngineWithAppId](sharedEngineWithAppId:delegate:) to initialize the RTC engine, otherwise, the CDN live streaming may fail.

 @param channelId A string acting as the unique channel name for the AgoraRTC session. The string length must be less than 64 bytes.
 Supported character scopes are: a-z, A-Z, 0-9, space, !#$%&()+-:;&le;.,>?@[]^_{|}~

 @param info (Optional) Additional information about the channel that developers may need to add. This parameter can be set to NIL or contain channel related information. Other users in the channel will not receive this message.

 Note: When joining a channel, the SDK calls setCategory(AVAudioSessionCategoryPlayAndRecord) to set AVAudioSession to PlayAndRecord mode. The app should not set it to any other mode. When setting to this mode, the sound being played (for example a ringtone) will be interrupted.

 @param uid User ID: A 32-bit unsigned integer with a value ranging from 1 to (2^32-1). The uid must be unique. If a uid is not assigned (or set to 0), the SDK assigns one and returns it in the joinSuccessBlock callback function. Your app must record and maintain the returned value since the SDK does not maintain its value.
 @param joinSuccessBlock Returns that the user has successfully joined the specified channel. Same as [didJoinChannel]([AgoraRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]). If nil, the [didJoinChannel]([AgoraRtcEngineDelegate rtcEngine:didJoinChannel:withUid:elapsed:]) callback function will be triggered.

 @return * 0: Success. * < 0: Failure.
 */
- (int)joinChannelByToken:(NSString * _Nullable)token
                channelId:(NSString * _Nonnull)channelId
                     info:(NSString * _Nullable)info
                      uid:(NSUInteger)uid
              joinSuccess:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))joinSuccessBlock;

/** Allows a user to leave a channel, such as hanging up or exiting a call.

After joining a channel, the user must call the leaveChannel method to end the call before joining another one.

This method returns 0 if the user has successfully left the channel and releases all resources related to the call.

This method is called asynchronously, and the user has not actually left the channel when the call returns. Once the user leaves the channel, the SDK triggers the [didLeaveChannelWithStats]([AgoraRtcEngineDelegate rtcEngine:didLeaveChannelWithStats:]) callback function.

 Note:

- If you call [destroy](destroy) immediately after leaveChannel, the leaveChannel process will be interrupted, and the SDK will not trigger the [didLeaveChannelWithStats]([AgoraRtcEngineDelegate rtcEngine:didLeaveChannelWithStats:]) callback function.

- When this method is called, the SDK will deactivate the audio session on iOS by default, and may affect other Apps. If you do not want this default behavior, use [setAudioSessionOperationRestriction](setAudioSessionOperationRestriction:) to set `AgoraAudioSessionOperationRestrictionDeactivateSession` so that when you call [leaveChannel](leaveChannel:), the SDK will not deactivate the audio session.

 @param leaveChannelBlock The callback indicates that a user has left the channel, and provides the statistics of this call, see [AgoraChannelStats](AgoraChannelStats) for details.

 @return * 0: Success. * < 0: Failure.
 */
- (int)leaveChannel:(void(^ _Nullable)(AgoraChannelStats * _Nonnull stat))leaveChannelBlock;

/** Renews the Token.

The Token expires after a certain period of time once the Token schema is enabled when:

  - The [tokenPrivilegeWillExpire]([AgoraRtcEngineDelegate rtcEngine:tokenPrivilegeWillExpire:]) callback function is triggered, or
  - The [didOccurError]([AgoraRtcEngineDelegate rtcEngine:didOccurError:]) callback function reports the AgoraErrorCodeTokenExpired(-109) error, or
  - The [rtcEngineRequestToken]([AgoraRtcEngineDelegate rtcEngineRequestToken:]) callback function reports the AgoraErrorCodeTokenExpired(-109) error.

 Note: Agora recommends using the [rtcEngineRequestToken]([AgoraRtcEngineDelegate rtcEngineRequestToken:]) callback function to report the AgoraErrorCodeTokenExpired(-109) error, not using the [didOccurError]([AgoraRtcEngineDelegate rtcEngine:didOccurError:]) callback function.

 The app should retrieve a new Token and call this method to renew it. Failure to do so will result in the SDK disconnecting from the server.

 @param token New Token.

 @return * 0: Success. * < 0: Failure.
 */
- (int)renewToken:(NSString * _Nonnull)token;


#pragma mark Core Audio

/**-----------------------------------------------------------------------------
 * @name Core Audio
 * -----------------------------------------------------------------------------
 */

/** Enables the audio function.

 This function is enabled by default.

 Note: This method enables the internal engine and still works after [leaveChannel]([AgoraRtcEngineKit leaveChannel:]) is called. You can call enableAudio either before or after joining a channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableAudio;

/** Disables/Re-enables the local audio function.

When an App joins a channel, the audio function is enabled by default. This method disables or re-enables the local audio function, that is, to stop or restart local audio capturing and handling.

This method does not affect receiving or playing the remote audio streams, and is applicable to scenarios where the user wants to receive the remote audio streams without sending any audio stream to other users in the channel.

The [didMicrophoneEnabled]([AgoraRtcEngineDelegate rtcEngine:didMicrophoneEnabled:]) callback function will be triggered once the local audio function is disabled or re-enabled.

Note:

Call this method after [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:).

This method is different from [muteLocalAudioStream](muteLocalAudioStream:) and [muteRecordingSignal](muteRecordingSignal:):

- [enableLocalAudio](enableLocalAudio:): Disables/Re-enables the local audio capturing and handling.

- [muteLocalAudioStream](muteLocalAudioStream:): Stops/Continues sending the local audio streams.

- [muteRecordingSignal](muteRecordingSignal:): Mutes/Unmutes the sound captured by the microphone.

 @param enabled * YES: Re-enable the local audio function, that is, to start the local audio capturing and handling.
 * NO: Disable the local audio function, that is, to stop local audio capturing and handling.
 @return * 0: Success. * < 0: Failure.
 */
- (int)enableLocalAudio:(BOOL)enabled;

/** Disables the audio function.

 Note: This method controls the underlying states of the Agora Engine and can be called either within or outside the channel. This method is still valid after a user leaves the channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)disableAudio;

/** Sets the audio parameters and application scenarios.

 Note:

 * setAudioProfile must be called before [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:).
 * In the communication mode, you can set the profile but not the scenario.
 * In the communication and live-broadcast mode, the bitrate may be different from your settings due to network self-adaptation.
 * In scenarios involving music education, Agora recommends setting profile as AgoraAudioProfileMusicHighQuality(4) and scenario as AgoraAudioScenarioGameStreaming(3).

 @param profile  Set the sampling rate, bitrate, encode mode, and the number of channels:: AgoraAudioProfile
 @param scenario Set the audio application scenario: AgoraAudioScenario

 @return * 0: Success. * < 0: Failure.
 */
- (int)setAudioProfile:(AgoraAudioProfile)profile
              scenario:(AgoraAudioScenario)scenario;

/** Adjusts the recording volume.

 @param volume Recording volume. The value ranges between 0 and 400:

 * 0: Mute
 * 100: Original volume
 * 400: (Maximum) Four times the original volume with signal clipping protection

 @return * 0: Success. * < 0: Failure.
 */
- (int)adjustRecordingSignalVolume:(NSInteger)volume;

/** Adjusts the playback volume.

 @param volume Playback volume. The value ranges between 0 and 400:

 * 0: Mute
 * 100: Original volume
 * 400: (Maximum) Four times the original volume with signal clipping protection

 @return * 0: Success. * < 0: Failure.
 */
- (int)adjustPlaybackSignalVolume:(NSInteger)volume;

#if TARGET_OS_IPHONE
/** Sets the default audio route.

 This method sets whether the received audio is routed to the earpiece or speakerphone before joining the channel. If the user does not call this method, the audio is routed to the earpiece by default.

 If you need to change the audio route after joining the channel, call [setEnableSpeakerphone](setEnableSpeakerphone:).

 Note:

 * This method applie to iOS only.
 * This method only works in audio mode.
 * Call this method before using [joinChannel](joinChannelByToken:channelId:info:uid:joinSuccess:).

 The default settings for each mode:

 * Voice: Earpiece
 * Video: Speakerphone. If the user in a communication channel has called [disableVideo](disableVideo) or if the user has called [muteLocalVideoStream](muteLocalVideoStream:) and [muteAllRemoteVideoStreams](muteAllRemoteVideoStreams:), the audio route is switched back to the earpiece automatically.
 * Live Broadcast: Speakerphone
 * Gaming Voice: Speakerphone

 @param defaultToSpeaker * YES: Route audio to the speakerphone.
 * NO: Route audio to the earpiece.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setDefaultAudioRouteToSpeakerphone:(BOOL)defaultToSpeaker;

/** Enables the audio routing to the speaker.

 This method sets whether the audio is routed to the speaker.

 Note:

 * This method applie to iOS only.
 * Ensure that you have successfully called the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) method before calling this method.
 * The SDK calls setCategory(AVAudioSessionCategoryPlayAndRecord) with options to configure the headset/speaker, so this method applies to all the playing audio in the system.
 * After this method is called, the SDK returns the [didAudioRouteChanged]([AgoraRtcEngineDelegate rtcEngine:didAudioRouteChanged:]) callback function, indicating that the audio routing has changed.
 * This method does not take effect when using a headset.

 @param enableSpeaker * YES: Route audio to the speakerphone.
 * NO: Route audio to the earpiece.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setEnableSpeakerphone:(BOOL)enableSpeaker;

/** Checks whether the speakerphone is enabled.

 This method applies to iOS only.

 @return * YES: The speakerphone is enabled, and the audio will be played from the speakerphone.
 * NO: The speakerphone is not enabled, and the audio will be played from devices other than the speakerphone, for example, the headset or earpiece.
 */
- (BOOL)isSpeakerphoneEnabled;
#endif

/** Mutes the recording signal.

 This method enables the user to hear only the mixed audio, but not the microphone when [startAudioMixing] (startAudioMixing:loopback:replace:cycle:) is called.

 @param muted * YES: Mute the recording signal. Once enabled, the use will hear the mixed audio only.
 * NO: Unmute the recording signal.

 @return * 0: Success. * < 0: Failure.
 */
-(int)muteRecordingSignal:(BOOL)muted;

/** Enables the SDK to regularly report to the application on which user is talking and the speaker's volume.

 @param interval Time interval between two consecutive volume indications:

 * &le; 0: Disables the volume indication
 * \> 0: The time interval (ms) between two consecutive volume indications. Agora recommends setting it to a minimum of 200 ms. Once the method is enabled, the SDK returns the volume indications at the set time interval in the [reportAudioVolumeIndicationOfSpeakers]([AgoraRtcEngineDelegate rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:]) and [audioVolumeIndicationBlock](audioVolumeIndicationBlock:) callback function, regardless of whether anyone is speaking in the channel.

 @param smooth The smoothing factor setting the sensitivity of the audio volume indicator. The value ranges between 0 and 10. The larger the value, the more sensitive the indicator. The recommended value is 3.

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableAudioVolumeIndication:(NSInteger)interval
                            smooth:(NSInteger)smooth;

/** Stops sending the local audio stream.

 Use this method to stop/start sending the local audio stream.

 Note: When set to YES, this method does not disable the microphone and thus does not affect any ongoing recording.

 @param mute * YES: Stops sending the local audio stream.
 * NO: Send the local audio stream.

 @return * 0: Success. * < 0: Failure.
 */
- (int)muteLocalAudioStream:(BOOL)mute;

/** Stops receiving a specified remote user’s audio stream.

 Note: If you have called [muteAllRemoteAudioStreams](muteAllRemoteAudioStreams:)(YES) to mute all remote audio streams, please call [muteAllRemoteAudioStreams](muteAllRemoteAudioStreams:)(NO) before using this method. [muteAllRemoteAudioStreams](muteAllRemoteAudioStreams:) sets all the remote streams, while [muteRemoteAudioStream](muteRemoteAudioStream:mute:) sets a specified stream.

 @param uid  User ID of the specified remote user.
 @param mute * YES: Stop receiving a specified remote user’s audio stream.
 * NO: Receive a specified remote user’s audio stream.

 @return * 0: Success. * < 0: Failure.
 */
- (int)muteRemoteAudioStream:(NSUInteger)uid mute:(BOOL)mute;

/** Stops receiving all remote users' audio streams.

 @param mute * YES: Stop receiving all remote users' audio streams.
 * NO: Receive all remote users' audio streams.

 @return * 0: Success. * < 0: Failure.
 */
- (int)muteAllRemoteAudioStreams:(BOOL)mute;

/** Sets whether to stop receiving all remote users' audio streams by default.

 @param mute * YES: Stop receiving all remote users' audio streams by default.
 * NO: (Default) Receive all remote users' audio streams by default.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setDefaultMuteAllRemoteAudioStreams:(BOOL)mute;


#pragma mark Core Video

/**-----------------------------------------------------------------------------
 * @name Core Video
 * -----------------------------------------------------------------------------
 */

/** Enables the video mode.

The app can call this method either before entering a channel or during a call. If the method is called before entering a channel, the service starts in the video mode. If the method is called during a call, the app switches from the audio to video mode.

To disable the video, call the disableVideo method.

Note: This method controls the underlying states of the Agora Engine, and is still valid after the user leaves the channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableVideo;

/** Disables the video mode.

   The app may call this method before entering a channel or during a call. If the method is called before entering a channel, the service starts in audio mode. If the method is called during a call, it switches from the video to audio mode. To enable the video mode, call the [enableVideo](enableVideo) method.

 Note: This method controls the underlying states of the Agora Engine, and is still valid after the user leaves the channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)disableVideo;

/** Disables the local video.

This method disables the local video. Only applicable when the user wants to watch the remote video without sending any video stream to the other user.

Call this method after [enableVideo](enableVideo), otherwise, this method may not work properly.

 After enableVideo is called, the local video will be enabled by default. This method is used to disable the local video while the remote video remains unaffected.

 Note: This method controls the underlying video engine states and is still active after a user leaves the channel.

 @param enabled Whether to disable the local video, including the capturer, renderer, and sender:

 * YES: (Default) Enable the local video.
 * NO: Disable the local video. Once the local video is disabled, the remote users can no longer receive the video stream of this user, while this user can still receive the video streams of other remote users.

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableLocalVideo:(BOOL)enabled;

/** Sets the video encoder configuration.

Each configuration profile corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.

The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until a successful configuration is found.

 If you do not set the video profile after joining the channel, call this method before enableVideo to shorten the time of the first frame showing.

 Note: Since v2.3.0, the following APIs are deprecated:

 - [setVideoProfile](setVideoProfile:swapWidthAndHeight:)
 - [setVideoResolution](setVideoResolution:andFrameRate:bitrate:)

 @param config Video encoder configuration: AgoraVideoEncoderConfiguration
 @return * 0: Success. * < 0: Failure.
 */
- (int)setVideoEncoderConfiguration:(AgoraVideoEncoderConfiguration * _Nonnull)config;

/** Sets the local video view.

This method configures the video display settings on the local machine.

The app calls this method to bind each video window (view) of the local video streams and configures the video display settings. Call this method after initialization to configure the local video display settings before entering a channel. After leaving the channel, the binding is still valid, which means the window will still display. To unbind the view, set the view value to nil when calling setupLocalVideo.

 @param local Video canvas information: AgoraRtcVideoCanvas

 @return * 0: Success. * < 0: Failure.
 */
- (int)setupLocalVideo:(AgoraRtcVideoCanvas * _Nullable)local;

/** Sets the remote video view.

This method binds the remote user to the video display window (sets the view for the user of the specified uid).

  Typically the app specifies the uid of the remote video in the method call before the user joins a channel.

   If the remote uid is unknown to the app, set it later when the app receives the [userJoinedBlock]([AgoraRtcEngineKit userJoinedBlock:]) event.

  If the Video Recording function is enabled, the Video Recording Service joins the channel as a dummy client, causing other clients to also receive the [didJoinedOfUid]([AgoraRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:]) event. Do not bind the dumb client to the app view because it does not send any video streams. If your app cannot recognize the dumb client, bind it with the view when the [firstRemoteVideoDecodedOfUid]([AgoraRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:]) event is triggered.

  To unbind the user with the view, set the view to nil. After the user has left the channel, the SDK unbinds the remote user.

 @param remote Video canvas information: AgoraRtcVideoCanvas

 @return * 0: Success. * < 0: Failure.
 */
- (int)setupRemoteVideo:(AgoraRtcVideoCanvas * _Nonnull)remote;

/** Sets the local video display mode.

 This method may be invoked multiple times during a call, to change the display mode.

 @param mode Local video display mode: AgoraVideoRenderMode

 @return * 0: Success. * < 0: Failure.
 */
- (int)setLocalRenderMode:(AgoraVideoRenderMode)mode;

/** Sets the remote video display mode.

This method can be invoked multiple times during a call to change the display mode.

 @param uid  User id of the remote user sending the video streams.
 @param mode Video display mode: AgoraVideoRenderMode

 @return * 0: Success. * < 0: Failure.
 */
- (int)setRemoteRenderMode:(NSUInteger)uid
                      mode:(AgoraVideoRenderMode)mode;

/** Starts the local video preview before joining the channel.

 Before starting the preview, you must:

 - Call [setupLocalVideo](setupLocalVideo:) to set up the local preview window and configure the attributes.
 - Call [enableVideo](enableVideo) to enable video.

Note: Once startPreview is called to start the local video preview, if you leave the channel by calling [leaveChannel](leaveChannel:), the local video preview remains until you call stopPreview to disable it.

 @return * 0: Success. * < 0: Failure.
 */
- (int)startPreview;

/** Stops the local video preview and the video.

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopPreview;

/** Stops sending the local video stream.

 Note: When set to YES, this method does not disable the camera, and thus does not affect the retrieval of the local video stream. This method responds faster compared to [enableLocalVideo](enableLocalVideo:) which controls the sending of local video streams.

 @param mute Whether to send the local video stream:

 * YES: Stop sending the local video stream.
 * NO: Send the local video stream.

 @return * 0: Success. * < 0: Failure.
 */
- (int)muteLocalVideoStream:(BOOL)mute;

/** Stops receiving all remote users' video streams.

 @param mute * YES: Stop receiving all remote users' video streams.
 * NO: (Default) Receive all remote users' video streams.

 @return * 0: Success. * < 0: Failure.
 */
- (int)muteAllRemoteVideoStreams:(BOOL)mute;

/** Stops receiving all remote users' video streams by default.

 @param mute * YES: Stop receiving all remote users' video streams by default.
 * NO: (Default) Receive all remote users' video streams by default.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setDefaultMuteAllRemoteVideoStreams:(BOOL)mute;

/** Stops receiving a specified remote user’s video stream.

Note: If you called [muteAllRemoteVideoStreams](muteAllRemoteVideoStreams:) and set to YES to stop receiving all remote video streams, ensure that muteAllRemoteVideoStreams is called and set to NO before calling this method.

 @param uid  User ID of the specified remote user.
 @param mute * YES: Stop receiving a specified remote user’s video stream.
 * NO: Receive a specified remote user’s video stream.

 @return * 0: Success. * < 0: Failure.
 */
- (int)muteRemoteVideoStream:(NSUInteger)uid
                        mute:(BOOL)mute;


#pragma mark Miscellaneous Audio Control

/**-----------------------------------------------------------------------------
 * @name Miscellaneous Audio Control
 * -----------------------------------------------------------------------------
 */

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
/** Enables loopback recording.

 Note: This method applies to macOS only.

 If you enable loopback recording, the output of the sound card will be mixed into the audio stream sent to the other end.

 Note: macOS does not support loopback of the default sound card. If you need to use this method, please use a virtual sound card and pass its name to the deviceName parameter. Agora has tested and recommends using soundflower.

 @param enabled    * YES: Enable loopback recording
 * NO: Disable loopback recording

 @param deviceName Device name of the sound card
 @return * 0: Success. * < 0: Failure.
 */
-(int)enableLoopbackRecording:(BOOL)enabled
                   deviceName:(NSString * _Nullable)deviceName;
#endif

#if TARGET_OS_IPHONE
/** Sets the audio session operation restriction. (iOS only)

 The SDK and the app can both configure the audio session by default. The app may occasionally use other applications or third-party components to manipulate the audio session and restrict the SDK from doing so. This method allows the app to restrict the SDK's manipulation of the audio session.

 You can call this method at any time to return the control of the audio sessions to the SDK.

 Note: This method restricts the SDK's manipulation of the audio session. Any operation to the audio session relies solely on the app, other applications, or third-party components.

 @param restriction The operational restriction (bit mask) of the SDK on the audio session. See [AgoraAudioSessionOperationRestriction](AgoraAudioSessionOperationRestriction) for details.

 */
- (void)setAudioSessionOperationRestriction:(AgoraAudioSessionOperationRestriction)restriction;
#endif


#pragma mark In Ear Monitor

/**-----------------------------------------------------------------------------
 * @name In-Ear Monitor
 * -----------------------------------------------------------------------------
 */

#if TARGET_OS_IPHONE

/** Enables in-ear monitoring.

 Note: This method applies to iOS only.

 @param enabled * YES: Enable in-ear monitoring * NO: Disable in-ear monitoring

 @return * 0: Success. * < 0: Failure.
  */
- (int)enableInEarMonitoring:(BOOL)enabled;

/** Sets the volume of the in-ear monitor.

 Note: This method applies to iOS only.

 @param volume The volume of the in-ear monitor. The value ranges between 0 and 100 (default).

 @return * 0: Success. * < 0: Failure.
 */
- (int)setInEarMonitoringVolume:(NSInteger)volume;
#endif


#pragma mark Audio Sound Effect

/**-----------------------------------------------------------------------------
 * @name Audio Sound Effect
 * -----------------------------------------------------------------------------
 */

/** Changes the voice pitch of the local speaker.

 @param pitch Voice frequency. The lower the value, the lower the voice pitch. The default value is 1.0, which means no change to the local voice pitch.

 @return * 0: Success. * -1: Failure.
 */
- (int)setLocalVoicePitch:(double)pitch;

/** Sets the local voice equalization effect.

 @param bandFrequency The band frequency. The value ranges between 0 and 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz. See AgoraAudioEqualizationBandFrequency for details.
 @param gain          Gain of each band in dB. The value ranges between -15 and 15. The default value is 0.

 @return * 0: Success. * -1: Failure.
*/
- (int)setLocalVoiceEqualizationOfBandFrequency:(AgoraAudioEqualizationBandFrequency)bandFrequency withGain:(NSInteger)gain;

/** Sets the local voice reverberation.

 @param reverbType Reverberation type: AgoraAudioReverbType
 @param value      The value sets the effect of the reverberation type, see AgoraAudioReverbType for the value range.

 @return * 0: Success. * -1: Failure.
 */
- (int)setLocalVoiceReverbOfType:(AgoraAudioReverbType)reverbType withValue:(NSInteger)value;


#pragma mark Audio Mixing

/**-----------------------------------------------------------------------------
 * @name Audio Mixing
 * -----------------------------------------------------------------------------
 */

/** Starts audio mixing.

  This method mixes the specified local audio file with the audio stream from the microphone; or, it replaces the microphone's audio stream with the specified local audio file. You can choose whether the other user can hear the local audio playback and specify the number of playback loops. This method also supports online music playback.

 When the audio mixing file playback stops after calling this method, the [rtcEngineLocalAudioMixingDidFinish]([AgoraRtcEngineDelegate rtcEngineLocalAudioMixingDidFinish:]) callback function will be triggered.

 Note:

 * To use this method, ensure that the iOS device version is 8.0+.
 * Call this method when you are in a channel, otherwise, it may cause issues.

 @param filePath Name and path of the local or online audio file to mix. Supported audio formats: mp3, aac, m4a, 3gp, and wav.
 @param loopback * YES: Only the local user can hear the remix or the replaced audio stream.
 * NO: Both users can hear the remix or the replaced audio stream.

 @param replace * YES: The content of the audio file replaces the audio stream from the microphone.
 * NO: Local audio file mixed with the audio stream from the microphone.

 @param cycle Number of playback loops:

 * Positive integer: Number of playback loops
 * -1：Infinite playback loops

 @return * 0: Success. * < 0: Failure.
 */
- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle;

/** Stops audio mixing.

 Call this API method when you are in a channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopAudioMixing;

/** Pauses audio mixing.

 Call this API method when you are in a channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)pauseAudioMixing;

/** Resumes audio mixing.

 Call this API method when you are in a channel.

 @return * 0: Success. * < 0: Failure.
 */
- (int)resumeAudioMixing;

/** Adjusts the volume while audio mixing.

 Call this API method when you are in a channel.

 @param volume Volume. The value ranges between 0 and 100 (default).
 @return * 0: Success. * < 0: Failure.
 */
- (int)adjustAudioMixingVolume:(NSInteger)volume;

/** Retrieves the duration (ms) of audio mixing.

 Call this API method when you are in a channel.

 @return * Returns the audio mixing duration if successful. * < 0: Failure.
 */
- (int)getAudioMixingDuration;

/** Retrieves the playback position (ms) of the audio.

 Call this API method when you are in a channel.

 @return * Returns the current position of the audio mixing if successful. * < 0: Failure.
 */
- (int)getAudioMixingCurrentPosition;

/** Sets the playback position of the audio mixing file to a different start position (default plays from the beginning).

 @param pos Integer. The time (ms) to start playing the audio mixing file.

 @return * 0: Success. * < 0: Failure.

 */
- (int)setAudioMixingPosition:(NSInteger)pos;


#pragma mark Audio Effect Playback

/**-----------------------------------------------------------------------------
 * @name Audio Effect Playback
 * -----------------------------------------------------------------------------
 */

/** Returns the volume of the sound effects.

The value ranges between 0.0 and 100.0.

@return * Returns the volume if successful.
* < 0: Failure.
 */
- (double)getEffectsVolume;

/** Sets the volume of the audio effects.

 @param volume Volume of the audio effects. The value ranges between 0.0 and 100.0 (default).

 @return * 0: Success. * < 0: Failure.
 */
- (int)setEffectsVolume:(double)volume;

/** Adjusts the volume of the specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.
 @param volume Volume of the audio effect. The value ranges between 0.0 and 100.0 (default).

 @return * 0: Success. * < 0: Failure.
 */
- (int)setVolumeOfEffect:(int)soundId
              withVolume:(double)volume;

/** Plays the specified audio effect.

You can use this method to add specific audio effects for specific scenarios, for example, gaming. When the audio effect file playback is finished, the [rtcEngineDidAudioEffectFinish]([AgoraRtcEngineDelegate rtcEngineDidAudioEffectFinish:soundId:]) callback method will be triggered。

 @param soundId ID of the specified audio effect. Each audio effect has a unique ID.
 If the audio effect is preloaded into the memory through [preloadEffect](preloadEffect:filePath:), ensure that the soundId value is set to the same value as in [preloadEffect](preloadEffect:filePath:).
 @param filePath The absolute path of the audio effect file.
 @param loopCount Set the number of times the audio effect loops:

 * 0: Play the audio effect once.
 * 1: Play the audio effect twice.
 * -1: Play the audio effect in a loop indefinitely, until [stopEffect](stopEffect:) or [stopAllEffects](stopAllEffects) is called.

 @param pitch Pitch of the audio effect. The value ranges between 0.5 and 2. The default value is 1 (no change to the pitch). The lower the value, the lower the pitch.
 @param pan Spatial position of the audio effect. The value ranges between -1.0 and 1.0.

 * 0.0: The audio effect displays ahead.
 * 1.0: The audio effect displays to the right.
 * -1.0: The audio effect displays to the left.

 @param gain Volume of the audio effect. The value ranges between 0.0 and 100.0 (default). The lower the value, the lower the volume of the audio effect.
 @param publish Whether to publish the specified audio effect to the remote stream:

 * YES: The audio effect, played locally, is published to the Agora Cloud and the remote users can hear it.
 * NO: The audio effect, played locally, is not published to the Agora Cloud and the remote users cannot hear it.

 @return * 0: Success. * < 0: Failure.
 */
- (int)playEffect:(int)soundId
         filePath:(NSString * _Nullable)filePath
        loopCount:(int)loopCount
            pitch:(double)pitch
              pan:(double)pan
             gain:(double)gain
          publish:(BOOL)publish;

/** Stops playing a specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopEffect:(int)soundId;

/** Stops playing all audio effects.
 */
- (int)stopAllEffects;

/** Preloads a specified audio effect file to the memory.

To ensure smooth communication, limit the size of the audio effect file. Agora recommends using this method to preload the audio effect before calling [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:).

Supported audio formats: mp3, aac, m4a, 3gp, and wav.

 @param soundId  ID of the audio effect. Each audio effect has a unique ID.
 @param filePath Absolute path of the audio effect file.

 @return * 0: Success. * < 0: Failure.
 */
- (int)preloadEffect:(int)soundId
            filePath:(NSString * _Nullable)filePath;

/** Releases a specified preloaded audio effect from the memory.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success. * < 0: Failure.
 */
- (int)unloadEffect:(int)soundId;

/** Pauses a specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success. * < 0: Failure.
 */
- (int)pauseEffect:(int)soundId;

/** Pauses all audio effects.

 @return * 0: Success. * < 0: Failure.
 */
- (int)pauseAllEffects;

/** Resumes playing a specified audio effect.

 @param soundId ID of the audio effect. Each audio effect has a unique ID.

 @return * 0: Success. * < 0: Failure.
 */
- (int)resumeEffect:(int)soundId;

/** Resumes playing all audio effects.

 @return * 0: Success. * < 0: Failure.
 */
- (int)resumeAllEffects;


#pragma mark Audio Recorder

/**-----------------------------------------------------------------------------
 * @name Audio Recorder
 * -----------------------------------------------------------------------------
 */

/** Starts an audio recording.

 The SDK allows recording during a call. Supported formats:

 * .wav: Large file size with high sound fidelity
 * .aac: Small file size with low sound fidelity

 Ensure that the saving directory in the app exists and is writable. This method is usually called after the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) method. The recording automatically stops when the [leaveChannel](leaveChannel:) method is called.

 @param filePath Full file path of the recording file. The string of the file name is in UTF-8.
 @param quality  Audio recording quality: AgoraAudioRecordingQuality

 @return * 0: Success. * < 0: Failure.
 */
- (int)startAudioRecording:(NSString * _Nonnull)filePath
                   quality:(AgoraAudioRecordingQuality)quality;

/** Stops an audio recording on the client.

 Note: You can call this method before calling [leaveChannel](leaveChannel:); else, the recording automatically stops when the leaveChannel method is called.

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopAudioRecording;


#pragma mark Echo Test

/**-----------------------------------------------------------------------------
 * @name Echo Test
 * -----------------------------------------------------------------------------
 */

/** Starts an audio call test.

This method launches an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly.

To conduct the test:

- The user speaks, and the recording is played back within 10 seconds.
- If the user can hear the recording within 10 seconds, the audio devices and network connection are working properly.

 Note:

 * After calling this method, always call stopEchoTest to end the test. Otherwise, the app cannot run the next echo test, nor can it call the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) method to start a new call.
 * In the live broadcast mode, only the hosts can call this method. If the user has switched from a communication to live broadcast channel, the user must call [setClientRole](setClientRole:) to change the user role from the audience (default) to the host before using this method.
 @param successBlock callback function on successfully starting the echo test.

 @return * 0: Success. * < 0: Failure.
 */
- (int)startEchoTest:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))successBlock;

/** Stops the audio call test.

 @return * 0: Success. * < 0: Failure. For example, AgoraErrorCodeRefused(-5)：Failed to stop the echo test. It could be that the echo test is not running.
 */
- (int)stopEchoTest;


#pragma mark Custom Video Module

/**-----------------------------------------------------------------------------
 * @name Custom Video Module
 * -----------------------------------------------------------------------------
 */

/** Sets the video source.

In real-time communications, the Agora SDK uses the default video input source (the built-in camera) to publish streams. To use the external video source, call AgoraVideoSourceProtocol to set the custom video source and then use this method to add the external video source into the SDK.

 @param videoSource AgoraVideoSourceProtocol
 */
- (void)setVideoSource:(id<AgoraVideoSourceProtocol> _Nullable)videoSource;

/** Sets the local video renderer.

In real-time communications, the Agora SDK uses the default video renderer to render the video. To use the external video renderer, call AgoraVideoSinkProtocol to set the custom local video renderer and then use this method to add the external renderer into the SDK.

 @param videoRenderer AgoraVideoSinkProtocol
 */
- (void)setLocalVideoRenderer:(id<AgoraVideoSinkProtocol> _Nullable)videoRenderer;

/** Sets the remote video renderer.

 This method sets the remote local renderer. In real-time communications, the Agora SDK uses the default video renderer to render the video. To use the external video renderer, call AgoraVideoSinkProtocol to set the custom remote video renderer and then use this method to add the external renderer into the SDK.

  @param videoRenderer AgoraVideoSinkProtocol
 @param userId Remote user ID
*/
- (void)setRemoteVideoRenderer:(id<AgoraVideoSinkProtocol> _Nullable)videoRenderer forUserId:(NSUInteger)userId;

/** Retrieves the video source.

  @return AgoraVideoSourceProtocol
 */
- (id<AgoraVideoSourceProtocol> _Nullable)videoSource;

/** Retrieves the local video renderer.

 @return AgoraVideoSinkProtocol
 */
- (id<AgoraVideoSinkProtocol> _Nullable)localVideoRenderer;

/** Retrieves the video renderer of a specified remote user.

 @param userId Remote user ID
 @return AgoraVideoSinkProtocol
 */
- (id<AgoraVideoSinkProtocol> _Nullable)remoteVideoRendererOfUserId:(NSUInteger)userId;


#pragma mark External Audio Data

/**-----------------------------------------------------------------------------
 * @name External Audio Data (push-mode only)
 * -----------------------------------------------------------------------------
 */

/** Enables the external audio source.

 @param sampleRate       Sampling rate of the external audio source: 8000, 16000, 44100 or 48000.
 @param channelsPerFrame Number of the external audio source channels (two channels maximum).
 */
- (void)enableExternalAudioSourceWithSampleRate:(NSUInteger)sampleRate
                               channelsPerFrame:(NSUInteger)channelsPerFrame;

/** Disables the external audio source.
 */
- (void)disableExternalAudioSource;

/** Pushes the external audio frame to the Agora SDK for encoding.

 @param data      External audio data.
 @param samples   Sampling point for the push.
 @param timestamp Timestamp of the external audio frame to synchronize with the external video source.
 @return * 0: Success. * < 0: Failure.
 */
- (BOOL)pushExternalAudioFrameRawData:(void * _Nonnull)data
                              samples:(NSUInteger)samples
                            timestamp:(NSTimeInterval)timestamp;

/** Pushes the external audio frame to the sample buffer for encoding.

 @param sampleBuffer Sample buffer
 @return * YES: Success. * NO: Failure.
 */
- (BOOL)pushExternalAudioFrameSampleBuffer:(CMSampleBufferRef _Nonnull)sampleBuffer;


#pragma mark External Video Data

/**-----------------------------------------------------------------------------
 * @name External Video Data (push-mode only)
 * -----------------------------------------------------------------------------
 */

/** Configures the external video source.

 If an external video source is used, call this API before [enableVideo](enableVideo) or [startPreview](startPreview).

 @param enable Whether to use an external video source:

 * YES: Use external video source.
 * NO: Do not use external video source.

 @param useTexture Whether to use the texture as an input:

 * YES: Use the texture as an input.
 * NO: Do not use the texture as an input.

 @param pushMode Whether the external video source needs to call [pushExternalVideoFrame](pushExternalVideoFrame:) to send the video frame to the Agora SDK:

 * YES: Use the push mode.
 * NO: Use the pull mode (not supported yet).
 */
- (void)setExternalVideoSource:(BOOL)enable useTexture:(BOOL)useTexture pushMode:(BOOL)pushMode;

/** Pushes the External Video Frame

This method pushes the video frame using the AgoraVideoFrame class and passes it to the Agora SDK with the input format found in AgoraVideoFormat.
Call [setExternalVideoSource](setExternalVideoSource:useTexture:pushMode:) and set the pushMode parameter as YES before calling this method. Otherwise, it will return a failure after calling this method.

Note: This method supports pushing textured video frames in the live-broadcast mode only, not in the communication mode.

 @param frame Video frame containing the Agora SDK's encoded video data. See AgoraVideoFrame for details.
 @return * YES: Frame is pushed successfully.
 * NO: Failed to push the frame.
 */
- (BOOL)pushExternalVideoFrame:(AgoraVideoFrame * _Nonnull)frame;


#pragma mark Raw Audio Data

/**-----------------------------------------------------------------------------
 * @name Raw Audio Data
 * -----------------------------------------------------------------------------
 */

/** Sets the audio recording format for the onRecordAudioFrame callback function.

See [Modifying Raw Data](https://docs.agora.io/en/2.3.1/product/Interactive%20Broadcast/Quickstart%20Guide/rawdata_ios?platform=iOS) for details.

 @param sampleRate     Sampling rate of the data returned by onRecordAudioFrame, which can be set as 8000, 16000, 32000, 44100, or 48000.
 @param channel        Number of channels for the data returned by onRecordAudioFrame, which can be set as 1 or 2:

- 1: Mono
- 2: Dual-Track
 @param mode      Use mode of the onRecordAudioFrame callback function: AgoraAudioRawFrameOperationMode
 @param samplesPerCall Sample points of the data returned in onRecordAudioFrame. It is usually set as 1024 for stream pushing. samplesPerCall = (int)(sampleRate × sampleInterval), where sampleInterval &ge; 0.01 in seconds.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)setRecordingAudioFrameParametersWithSampleRate:(NSInteger)sampleRate
                                              channel:(NSInteger)channel
                                                 mode:(AgoraAudioRawFrameOperationMode)mode
                                       samplesPerCall:(NSInteger)samplesPerCall;
/** Sets the audio playback format for the onPlaybackAudioFrame callback function.

See [Modifying Raw Data](https://docs.agora.io/en/2.3.1/product/Interactive%20Broadcast/Quickstart%20Guide/rawdata_ios?platform=iOS) for details.

 @param sampleRate     Sampling rate in the callback data returned by onPlaybackAudioFrame, which can set be as 8000, 16000, 32000, 44100 or 48000.
 @param channel        Specifies the number of channels in the callback data returned by onPlaybackAudioFrame, which can be set as 1 or 2:

  * 1: Mono
  * 2: Dual-Track
 @param mode           Use mode of the onPlaybackAudioFrame callback function: AgoraAudioRawFrameOperationMode
 @param samplesPerCall Sample points of the data returned in onPlaybackAudioFrame. It is usually set as 1024 for stream pushing. samplesPerCall = (int)(sampleRate × sampleInterval), where sampleInterval &ge; 0.01 in seconds.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)setPlaybackAudioFrameParametersWithSampleRate:(NSInteger)sampleRate
                                             channel:(NSInteger)channel
                                                mode:(AgoraAudioRawFrameOperationMode)mode
                                      samplesPerCall:(NSInteger)samplesPerCall;

/** Sets the mixed audio format for the onMixedAudioFrame callback function.

See [Modifying Raw Data](https://docs.agora.io/en/2.3.1/product/Interactive%20Broadcast/Quickstart%20Guide/rawdata_ios?platform=iOS) for details.

 @param sampleRate     Sampling rate in the callback data returned by onMixedAudioFrame, which can set be as 8000, 16000, 32000, 44100, or 48000.
 @param samplesPerCall Sample points of the data returned in onMixedAudioFrame. It is usually set as 1024 for stream pushing. samplesPerCall = (int)(sampleRate × sampleInterval), where sampleInterval &ge; 0.01 in seconds.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setMixedAudioFrameParametersWithSampleRate:(NSInteger)sampleRate
                                   samplesPerCall:(NSInteger)samplesPerCall;


#pragma mark Watermark

/**-----------------------------------------------------------------------------
 * @name Watermark
 * -----------------------------------------------------------------------------
 */

/** Adds a watermark to the local video stream.

This method adds a PNG watermark to the local video stream for the recording device, channel audience, and CDN live audience to see and capture.

 To add the PNG file onto a CDN live publishing stream only, see the  [setLiveTranscoding](setLiveTranscoding:) method.

Note:

* The URL descriptions are different for local video streaming and CDN live streaming. In a local broadcast, url refers to the definite path of the added watermark file in the local video; while in a CDN live broadcast, url refers to the HTTP/HTTPS address of the added watermark image in the CDN live broadcast.
* The source file of the watermark image must be in the PNG file format. If the width and height of the PNG file differs from your settings in this method, the PNG file will be cropped to conform to your settings
* The Agora SDK supports adding only one watermark onto the live stream. The newly added watermark replaces the previous one.
* If you set orientationMode as Adaptive in the [setVideoEncoderConfiguration](setVideoEncoderConfiguration:) method, the watermark image rotates with the video frame and rotates around the upper left corner of the watermark image.

@param watermark Watermark image added to the local video stream: AgoraImage

@return * 0: Success. * < 0: Failure.
 */
- (int)addVideoWatermark:(AgoraImage * _Nonnull)watermark NS_SWIFT_NAME(addVideoWatermark(_:));

/** Removes the watermark image from the video stream added by [addVideoWatermark](addVideoWatermark:).

 @return * 0: Success. * < 0: Failure.
 */
- (void)clearVideoWatermarks;


#pragma mark Stream Fallback

/**-----------------------------------------------------------------------------
 * @name Stream Fallback
 * -----------------------------------------------------------------------------
 */

/** Sets the fallback option for the locally published stream based on the network conditions.

If the option is set to AgoraStreamFallbackOptionAudioOnly, the SDK will:

 * Disable the upstream video when the network cannot support both video and audio.
 * Re-enable the video when the network condition improves.

 When the locally published stream falls back to audio-only or when the audio stream switches back to the video, the [didLocalPublishFallbackToAudioOnly]([AgoraRtcEngineDelegate rtcEngine:didLocalPublishFallbackToAudioOnly:]) callback function will be triggered.

 Note: Agora does not recommend using this method for CDN live streaming, because the remote CDN live user will have a noticeable lag when the locally published stream falls back to audio-only.

 @param option Fallback options. The default value is AgoraStreamFallbackOptionDisabled, see AgoraStreamFallbackOptions for details.
 @return * 0: Success. * < 0: Failure.
 */
- (int)setLocalPublishFallbackOption:(AgoraStreamFallbackOptions)option;

/** Sets the fallback option for the remotely subscribed stream based on the network conditions.

If the option is set to AgoraStreamFallbackOptionAudioOnly, the SDK will automatically switch the video from a high-stream to a low-stream, or disable the video when the downlink network conditions cannot support both audio and video to guarantee the quality of the audio. The SDK monitors the network quality and re-enables the video stream when the network conditions improve.
 Once the locally published stream falls back to audio only, or the audio stream switches back to the video stream, the [didRemoteSubscribeFallbackToAudioOnly]([AgoraRtcEngineDelegate  rtcEngine:didRemoteSubscribeFallbackToAudioOnly:byUid:]) callback function will be triggered.

 @param option Fallback options for the remotely subscribed stream. The default value is AgoraStreamFallbackOptionVideoStreamLow, see AgoraStreamFallbackOptions for details.
 @return * 0: Success. * < 0: Failure.
 */
- (int)setRemoteSubscribeFallbackOption:(AgoraStreamFallbackOptions)option;


#pragma mark Dual Video Mode

/**-----------------------------------------------------------------------------
 * @name Dual Video Mode
 * -----------------------------------------------------------------------------
 */

/** Sets the stream mode to single- (default) or dual-stream mode. (Live broadcast only.)

If dual-stream mode is enabled, the receiver can choose to receive the high stream (high-resolution high-bitrate video stream), or low stream (low-resolution low-bitrate video stream).

 @param enabled The mode is in a single-video stream or dual-video stream:

 * YES: Dual-video stream
 * NO: (Default) Single-video stream

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableDualStreamMode:(BOOL)enabled;

/** Sets the remote user’s video stream type. Received by the local user when the remote user sends dual streams.

This method allows the app to adjust the corresponding video-stream type based on the size of the video window to reduce the bandwidth and resources.

 * If the remote user has enabled the dual-stream mode by calling [enableDualStreamMode](enableDualStreamMode:), the SDK will receive the high-video stream by default. You can use this method to switch to the low-video stream type.
 * If the dual-stream mode is not enabled, the SDK will receive the high-video stream by default.

 The method result will be returned in the [didApiCallExecute]([AgoraRtcEngineDelegate rtcEngine:didApiCallExecute:api:result:]) callback function. The Agora SDK receives the high-video stream by default to save the bandwidth. If needed, users may use this method to switch to the low-video stream.

 By default, the aspect ratio of the low-video stream is the same as the high-video stream. Once the resolution of the high-video stream is set, the system automatically sets the resolution, frame rate and bitrate for the low-video stream.

 @param uid        User ID
 @param streamType AgoraVideoStreamType

 @return * 0: Success. * < 0: Failure.
 */
- (int)setRemoteVideoStream:(NSUInteger)uid
                       type:(AgoraVideoStreamType)streamType;

/** Sets the default video-stream type for the video received by the local user when the remote user sends dual streams.

 @param streamType AgoraVideoStreamType

 @return * 0: Success. * < 0: Failure.
 */
- (int)setRemoteDefaultVideoStreamType:(AgoraVideoStreamType)streamType;


#pragma mark Encryption

/**-----------------------------------------------------------------------------
 * @name Encryption
 * -----------------------------------------------------------------------------
 */

/** Sets the encryption password to enable built-in encryption before joining a channel.

All users in a channel must set the same encryption password. The encryption password is automatically cleared once a user has left the channel.

  If the encryption password is not specified or set to empty, the encryption functionality will be disabled.

 Note: Do not use this method for CDN live streaming.

 @param secret Encryption password
 @return * 0: Success. * < 0: Failure.
 */
- (int)setEncryptionSecret:(NSString * _Nullable)secret;

/** Sets the built-in encryption mode.

 The Agora SDK supports built-in encryption, which is set to AES-128-XTS mode by default. Call this API method to set the encryption mode to use other encryption modes.

 All users in the same channel must use the same encryption mode and password.

 Refer to the information related to the AES encryption algorithm on the differences between the encryption modeme
 Call [setEncryptionSecret](setEncryptionSecret:) to enable the built-in encryption function before calling this method.

 Note: Do not use this method for CDN live streaming.

 @param encryptionMode Encryption mode: AgoraEncryptionMode

 @return * 0: Success. * < 0: Failure.
 */
- (int)setEncryptionMode:(NSString * _Nullable)encryptionMode;


#pragma mark Inject Stresam URL

/**-----------------------------------------------------------------------------
 * @name Inject Stresam URL
 * -----------------------------------------------------------------------------
 */

/** Adds a voice or video stream URL to a live broadcast.

 The [streamPublishedWithUrl]([AgoraRtcEngineDelegate rtcEngine:streamPublishedWithUrl:errorCode:]) callback returns its inject status.

 If this method is called successful, the server pulls the voice or video stream and injects it into a live channel. This is applicable to scenarios where all the audience members in the channel can watch a live show and interact with each other.

 The [didJoinedOfUid]([AgoraRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:]) and [firstRemoteVideoDecodedOfUid]([AgoraRtcEngineDelegate rtcEngine:firstRemoteVideoFrameOfUid:size:elapsed:]) callback functions will be triggered and a stream uid of 666 will be returned.

 @param url    HTTP/HTTPS address to add to the ongoing live broadcast. Valid protocols are RTMP, HLS, and FLV.
 @param config AgoraLiveInjectStreamConfig object which contains the configuration information for the added voice or video stream.
 @return * 0: Success. * < 0: Failure.
*/
- (int)addInjectStreamUrl:(NSString * _Nonnull)url config:(AgoraLiveInjectStreamConfig * _Nonnull)config;

/** Removes the voice or video stream URL from a live broadcast.

 If successful, the [didOfflineOfUid]([AgoraRtcEngineDelegate rtcEngine:didOfflineOfUid:reason:]) callback function will be triggered and a stream uid of 666 will be returned.

 @param url HTTP/HTTPS address of the added stream to remove.
 @return * 0: Success. * < 0: Failure.
 */
- (int)removeInjectStreamUrl:(NSString * _Nonnull)url;


#pragma mark CDN Publisher

/**-----------------------------------------------------------------------------
 * @name CDN Publisher
 * -----------------------------------------------------------------------------
 */

/** Adds a stream URL to where the host publishes the stream. (CDN live only.)

The host publishes the stream to the specified CDN live HTTP/HTTPS address. It triggers the callback [streamPublishedWithUrl]([AgoraRtcEngineDelegate rtcEngine:streamPublishedWithUrl:errorCode:]).

 Note:

 - Ensure that the user has joined the channel before calling this method.
 - This method only adds one stream URL each time it is called.
 - The URL may not contain special characters such as Chinese language characters.

 @param url  URL to where the host publishes the stream.
 @param transcodingEnabled Whether transcoding is enabled or not:

 - YES: Enable transcoding (transcoding refers to transcoding the video streams when publishing them to CDN live, often used for combining the video streams of multiple hosts in CDN live).
 - NO: Disable transcoding.

 @return * 0: Success. * < 0: Failure.

  - AgoraErrorCodeInvalidArgument(2): Invalid parameter, usually because the URL is nil or the string length is 0.
  - AgoraErrorCodeNotInitialized(7): You have not initialized the RTC Engine when publishing the stream.
 */
- (int)addPublishStreamUrl:(NSString * _Nonnull)url transcodingEnabled:(BOOL)transcodingEnabled;

/** Removes a stream URL. (CDN live only.)

This method removes the URL address in the CDN streaming.

 Note:

 * This method only removes one URL each time it is called.
 * The URL may not contain special characters such as Chinese language characters.

 @param url URL to where the host publishes the stream.

 @return * 0: Success. * < 0: Failure.
 */
- (int)removePublishStreamUrl:(NSString * _Nonnull)url;

/** Sets the video layout and audio for CDN live. (CDN live only.)

 @param transcoding See AgoraLiveTranscoding.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setLiveTranscoding:(AgoraLiveTranscoding *_Nullable)transcoding;


#pragma mark Data Stream

/**-----------------------------------------------------------------------------
 * @name Data Steam
 * -----------------------------------------------------------------------------
 */

/** Creates a data stream.

 Each user can have up to five simultaneous data channels.

 Note: Set both the reliable and ordered parameters to YES or NO. Do not set one as YES and the other as NO.

 @param streamId Stream ID
 @param reliable * YES: The recipients will receive data from the sender within 5 seconds. If the recipient does not receive the data within 5 seconds, the data channel will report an error to the app.
 * NO: The recipients will not receive any data, and therefore it will not report any errors for missing data.

 @param ordered  * YES: The recipients will receive the data in the order that they were sent.
 * NO: The recipients will not receive the data in the order that they were sent.

 @return * Returns the stream ID if successful. * < 0: Failure.
*/
- (int)createDataStream:(NSInteger * _Nonnull)streamId
               reliable:(BOOL)reliable
                ordered:(BOOL)ordered;

/** Sends data stream messages to all users in a channel.

The SDK has imposed the following restrictions on this method: Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB. Each client can send up to 6 kB of data per second. Each user can have up to five data channels simultaneously.

 Note: This method applies only to the communication mode or to the hosts in the live broadcast mode. If an audience in the live broadcast mode calls this method, the audience role may be changed to a host.

 @param streamId Stream ID returned by [createDataStream](createDataStream:reliable:ordered:).
 @param data   Data to send.

 @return * 0: Success.
 * < 0: Failure.
*/
- (int)sendStreamMessage:(NSInteger)streamId
                    data:(NSData * _Nonnull)data;


#pragma mark Miscellaneous Video Control

/**-----------------------------------------------------------------------------
 * @name Miscellaneous Video Control
 * -----------------------------------------------------------------------------
 */

/** Sets the preferences for the high-quality video.

This API only applies to the live broadcast scenario.

Under poor network conditions or the device's CPU is overloaded, the video quality may be affected. You can use this method to choose the video smoothness (frame rate) over the image quality or vice versa.

 @param preferFrameRateOverImageQuality Video quality preference:

 * YES: Frame rate preference over image quality.
 * NO: (Default) Image quality preference over frame rate.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setVideoQualityParameters:(BOOL)preferFrameRateOverImageQuality;

/** Sets the local video preview mirror mode.

 Use this method before startPreview, or the mirror mode will not take effect until you re-enable startPreview.

 @param mode Local video mirror mode: AgoraVideoMirrorMode

 @return * 0: Success. * < 0: Failure.
 */
- (int)setLocalVideoMirrorMode:(AgoraVideoMirrorMode)mode;


#pragma mark Customized Method (Technical Preview)

/**-----------------------------------------------------------------------------
 * @name Customized Method (Technical Preview)
 * -----------------------------------------------------------------------------
 */

/** Provides the technical preview functionalities or special customizations by configuring the SDK with JSON options.

 Note: The JSON options are not public by default. Agora is working on making commonly used JSON options public in a standard way. Contact [support@agora.io](mailto:support@agora.io) for more information.

 @param options SDK options in JSON format.
 */
- (int)setParameters:(NSString * _Nonnull)options;

/** Retrieves the Agora SDK's parameters for customization purposes.

 Note: This method is not public. Contact support@agora.io for more information.

 */
- (NSString * _Nullable)getParameter:(NSString * _Nonnull)parameter
                                args:(NSString * _Nullable)args;


#if TARGET_OS_IPHONE
#pragma mark Camera Control

/**-----------------------------------------------------------------------------
 * @name Camera Control
 * -----------------------------------------------------------------------------
 */

/** Switches between the front and rear cameras.

 Note: This method applies to iOS only, not to macOS.

 @return * 0: Success. * < 0: Failure.
 */
- (int)switchCamera;

/** Checks whether camera zoom is supported.

 Note: This method applies to iOS only, not to macOS.

 @return * YES: The device supports the camera zoom function
 * NO: The device does not support the camera zoom function
 */
- (BOOL)isCameraZoomSupported;

/** Checks whether camera flash is supported.

 Note:

 * This method applies to iOS only, not to macOS.
 * The app generally enables the front camera by default. If your front camera does not support front camera torch, this method will return No. If you want to check if the rear camera torch is supported, call switchCamera before using this method.

 @return * YES: The device supports the camera flash function
 * NO: The device does not support the camera flash function
 */
- (BOOL)isCameraTorchSupported;

/** Checks whether the manual focus is supported.

 Note: This method applies to iOS only, not to macOS.

 @return * YES: The device supports the manual focus function
 * NO: The device does not support the manual focus function
 */
- (BOOL)isCameraFocusPositionInPreviewSupported;

/** Checks whether the autofocus is supported.

 Note: This method applies to iOS only, not to macOS.

 @return * YES: The device supports the autofocus function
 * NO: The device does not support the autofocus function
 */
- (BOOL)isCameraAutoFocusFaceModeSupported;

/** Sets the camera zoom ratio.

 Note: This method applies to iOS only, not to macOS.

 @param zoomFactor The camera zoom factor. The value ranges between 1.0 and the maximum zoom supported by the device.

 @return When called successfully, it returns the set zoom factor. Otherwise, it returns a negative integer.
 */
- (CGFloat)setCameraZoomFactor:(CGFloat)zoomFactor;

/** Sets the manual focus position.

 Note: This method applies to iOS only, not to macOS.

 @param position Coordinates of the touch point in the view

 @return * YES: Success. * NO: Failure.
 */
- (BOOL)setCameraFocusPositionInPreview:(CGPoint)position;

/** Enables the camera flash.

 Note: This method applies to iOS only, not to macOS.

 @param isOn * YES: Enable the camera flash
 * NO: Disable the camera flash

 @return * YES: Success. * NO: Failure.
 */
- (BOOL)setCameraTorchOn:(BOOL)isOn;

/** Enables the camera autoFocus.

 Note: This method applies to iOS only, not to macOS.

 @param enable * YES: Enable the camera autofocus
 * NO: Disable the camera autofocus

 @return * YES: Success. * NO: Failure.
 */
- (BOOL)setCameraAutoFocusFaceModeEnabled:(BOOL)enable;

#endif


#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
#pragma mark Screen Capture

/**-----------------------------------------------------------------------------
 * @name Screen Capture
 * -----------------------------------------------------------------------------
 */

/** Starts screen sharing.

 Note: This method applies to macOS only.

 @param windowId Set to share the whole screen, a specified window, or a specified region:

 * Share the whole screen: Set windowId as 0 and set rect as nil.
 * Share the specified window: Set windowId not as 0. Each window has a windowId that is not 0.
 * Share the specified region: Set windowId as 0 and set rect not as nil. You can share the specified region, for example by dragging the mouse (the logic is implemented by yoursel). The specified region is a region on the whole screen. Currently, sharing a specified region in a specific window is not supported.
 @param captureFreq The captured frame rate. The value (mandatory) ranges between 1 fps and 15 fps.
 @param bitRate The captured bitrate.
 @param rect Specify the screen-sharing region. This parameter is valid when windowsId is set as 0. When you set rect as nil, the whole screen is shared.
 @return * 0: Success. * < 0: Failure.
 */
- (int)startScreenCapture:(NSUInteger)windowId
          withCaptureFreq:(NSInteger)captureFreq
                  bitRate:(NSInteger)bitRate
                  andRect:(CGRect)rect;

/** Stops screen sharing.

 Note: This method applies to macOS only.

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopScreenCapture;

/** Updates the screen-sharing region.

 Note: This method applies to macOS only.

 @param rect Specify the screen-sharing region. This parameter is valid when windowsId is set as 0, and when you set rect as nil, then the whole screen is shared.

 @return * 0: Success. * < 0: Failure.
 */
- (int)updateScreenCaptureRegion:(CGRect)rect;
#endif


#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
#pragma mark Device Manager (macOS)
/**-----------------------------------------------------------------------------
 * @name Device Manager (macOS)
 * -----------------------------------------------------------------------------
 */

/** Monitors the change of a device state.

 Note: This method applies to macOS only, not to iOS.

 Use this method to monitor the plugging and swapping of external audio/video devices, for example an external camera.

 @param enabled - YES: Enable the monitoring of a device state change.
 - NO: Disable the monitoring of a device state change.
 */
- (void)monitorDeviceChange:(BOOL)enabled;

/** Retrieves all the devices in the system.

 Note:

- This method applies to macOS only, not to iOS.
- Do not call this method in the main thread.

 This method returns an NSArray object, including all the audio/video devices in the system.
 Your app can use the AgoraRtcDeviceInfo array object to enumerate the devices.

 @param type Device type: AgoraMediaDeviceType
 @return When called successfully, it returns an AgoraRtcDeviceInfo NSArray object including all the devices.
 */
- (NSArray<AgoraRtcDeviceInfo *> * _Nullable)enumerateDevices:(AgoraMediaDeviceType)type;

/** Retrieves the device info; such as a recording, playback, or video capture device.

 Note: This method applies to macOS only, not to iOS.

 @param type Device type: AgoraMediaDeviceType
 @return When called successfully, it returns the device info of the device, see AgoraRtcDeviceInfo. Otherwise, it returns nil.
 */
- (AgoraRtcDeviceInfo * _Nullable)getDeviceInfo:(AgoraMediaDeviceType)type;

/** Sets the playback, recording, or audio-sampling device.

 Note: This method applies to macOS only, not to iOS.

 @param type    Device type: AgoraMediaDeviceType
 @param deviceId Device ID of the device, which can be fetched by calling [enumerateDevices](enumerateDevices:). The deviceId does not change when plugged or unplugged.
 @return * 0: Success. * < 0: Failure.
 */

- (int)setDevice:(AgoraMediaDeviceType)type deviceId:(NSString * _Nonnull)deviceId;

/** Retrieves the specified device's volume.

 Note: This method applies to macOS only, not to iOS.

 @param type Device type: AgoraMediaDeviceType
 @return * Returns the volume if successful
 * < 0: Failure.
 */
- (int)getDeviceVolume:(AgoraMediaDeviceType)type;

/** Sets the specified device's volume.

 Note: This method applies to macOS only, not to iOS.

 @param type   Device type: AgoraMediaDeviceType
 @param volume The volume to set. The value ranges between 0 and 100.
 @return * 0: Success. * < 0: Failure.
 */
- (int)setDeviceVolume:(AgoraMediaDeviceType)type volume:(int)volume;

/** Starts the microphone test.

 Note: This method applies to macOS only, not to iOS.

 This method tests whether the microphone works properly. Once the test starts, the SDK reports the volume information by using the [reportAudioVolumeIndicationOfSpeakers]([AgoraRtcEngineDelegate rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:]) callback function.

 @param indicationInterval Interval (ms) at which to report the microphone volume.
 @return * 0: Success. * < 0: Failure.
 */
- (int)startRecordingDeviceTest:(int)indicationInterval;

/** Stops the microphone test.

 Note: This method applies to macOS only, not to iOS.

 This method stops testing the microphone. You must call this method to stop the test after calling the [startRecordingDeviceTest](startRecordingDeviceTest:) method.

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopRecordingDeviceTest;

 /** Starts a playback device test.

 Note: This method applies to macOS only, not to iOS.

 This method tests whether the playback device works properly with the specified playback audio file.

 @param audioFileName File path of the audio file for the test, which is in UTF-8:

 - Supported File Format: wav, mp3, m4a, and aac
 - Supported File Sampling Rate: 8000, 16000, 32000, 44100, and 48000

 @return * 0: Success. * < 0: Failure.
 */
- (int)startPlaybackDeviceTest:(NSString * _Nonnull)audioFileName;

/** Stops the playback device test.

 Note: This method applies to macOS only, not to iOS.

 This method stops testing the playback device. You must call this method to stop the test after calling [startPlaybackDeviceTest](startPlaybackDeviceTest:).

 @return * 0: Success. * < 0: Failure.
 */
- (int)stopPlaybackDeviceTest;

/** Starts the capture device test.

 Note: This method applies to macOS only, not to iOS.

 This method tests whether the current video capture device works properly. Ensure that you have called [enableVideo](enableVideo) before calling this method and that the parameter view window is valid.

 @param view Input parameter, for displaying the video window.

 @return * 0: Success. * < 0: Failure.

 */
- (int)startCaptureDeviceTest:(NSView * _Nonnull)view;

/** Stops the capture device test.

 Note: This method applies to macOS only, not to iOS.

 This method stops testing the capture device. You must call this method to stop the test after calling [startCaptureDeviceTest](startCaptureDeviceTest:).

 @return * 0: Success. * < 0: Failure.

 */
- (int)stopCaptureDeviceTest;
#endif


#pragma mark Miscellaneous Methods

/**-----------------------------------------------------------------------------
 * @name Miscellaneous Methods
 * -----------------------------------------------------------------------------
 */

/** Retrieves the current call ID.

 When a user joins a channel on a client, a callId is generated to identify the call from the client. Feedback methods, such as the [rate](rate:rating:description:) and [complain](complain:description:) methods, must be called after the call ends, so feedback can be submitted to the SDK. These methods require the callId parameter.

 To use these feedback methods, use the getCallId method to retrieve the callId during the call to be passed as an argument into the feedback methods after the call ends.

 @return callId The current call ID.
 */
- (NSString * _Nullable)getCallId;

/** Allows the user to rate the call and is usually called after the call ends.

 @param callId      Call ID retrieved from the getCallId method.
 @param rating      The rating for the call between 1 (lowest score) to 10 (highest score).
 @param description (Optional) Description for the call. The string length must be less than 800 bytes.

 @return * 0: Success.
 * < 0: Failure.

     * Return AgoraErrorCodeInvalidArgument(-2)：The passed argument is invalid, for example, callId invalid.
     * Return AgoraErrorCodeNotReady(-3)：The SDK status is incorrect, for example, initialization failed.
 */
- (int)rate:(NSString * _Nonnull)callId
     rating:(NSInteger)rating
description:(NSString * _Nullable)description;

/** Allows a user to complain about the call quality.

The complaint is usually called after the call ends.

 @param callId      Call ID retrieved from the getCallId method.
 @param description (Optional) Description for the call. Character length must be less than 800 bytes.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)complain:(NSString * _Nonnull)callId
    description:(NSString * _Nullable)description;

/** Enables/Disables dispatching the delegate to the main queue.

 If disabled, the app should dispatch the UI operating to the main queue.

 @param enabled * YES: Dispatch the delegate method to the main queue.
 * NO: Do not dispatch the delegate methods to the main queue

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableMainQueueDispatch:(BOOL)enabled;

/** Returns the Agora SDK version.

 This method returns the string of the version number.

 @return The version of the current SDK in the string format. For example, 2.3.0
 */
+ (NSString * _Nonnull)getSdkVersion;

/** Enables the network test.

  This method tests the quality of the user’s network connection and is disabled by default.

Before users join a channel, call this method to check the uplink network quality.

This method consumes additional network traffic, which may affect the communication quality.

 Call [disableLastmileTest](disableLastmileTest) to disable the test immediately after receiving the  [lastmileQuality]([AgoraRtcEngineDelegate rtcEngine:lastmileQuality:]) callback function, and before the user joins the channel or switches the user role.

 Note: Do not call this method for hosts.

 @return * 0: Success. * < 0: Failure.
 */
- (int)enableLastmileTest;

/** Disables the quality test for the network connection.

 @return * 0: Success. * < 0: Failure.
 */
- (int)disableLastmileTest;

/** Specifies an SDK output log file.

The log file records all log data for the SDK’s operation. Ensure that the directory for the log file exists and is writable.

 Note: The default log file location is at Library/caches/agorasdk.log.

 @param filePath File path of the log file. The string of the log file is in UTF-8.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)setLogFile:(NSString * _Nonnull)filePath;

/** Sets the output log level of the SDK.

You can use one or a combination of the filters. The log level follows the sequence of OFF, CRITICAL, ERROR, WARNING, INFO, and DEBUG. Choose a level to see the logs preceding that level.

For example, if you set the log level to WARNING, you will see the logs within levels CRITICAL, ERROR and WARNING.

 @param filter Log filter level: AgoraLogFilter.

 @return * 0: Success.
 * < 0: Failure.
 */
- (int)setLogFilter:(NSUInteger)filter;

/** Returns the native handler of the SDK Engine.

 This interface is used to get native the C++ handler of the SDK engine used in special scenarios, such as register the audio and video frame observer.
 */
- (void * _Nullable)getNativeHandle;


#pragma mark Deprecated Methods

/**-----------------------------------------------------------------------------
 * @name Deprecated Methods
 * -----------------------------------------------------------------------------
 */

/** Initializes the AgoraRtcEngineKit object.

 **DEPRECATED** from v2.3.

 @see [sharedEngineWithAppId](sharedEngineWithAppId:delegate:)
 @param AppId    App ID issued to the application developers by Agora. Apply for a new one from Agora if the key is missing in your kit. Each project will be assigned a unique App ID. The App ID identifies your project and organization in the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) method to access the Agora Global Network, and enable one-to-one or one-to-more communication or live-broadcast sessions using a unique channel name for your App ID.
 @param errorBlock AgoraErrorCode
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)AppId
                                         error:(void(^ _Nullable)(AgoraErrorCode errorCode))errorBlock __deprecated_msg("use sharedEngineWithAppId:delegate: instead.");

/** Disables the audio function in the channel.

**DEPRECATED** from v2.3

 @see disableAudio
 @return * 0: Success. * < 0: Failure.
 */
- (int)pauseAudio __deprecated_msg("use disableAudio instead.");

/** Resumes the audio in the channel.

 **DEPRECATED** from v2.3

 @see enableAudio
 @return * 0: Success. * < 0: Failure.
 */
- (int)resumeAudio __deprecated_msg("use enableAudio instead.");

/** Sets the high-quality audio parameters.

 Replaced with [setAudioProfile](setAudioProfile:scenario:).

**DEPRECATED** from v2.3.

 @see [setAudioProfile](setAudioProfile:scenario:)
 @param fullband Full-band codec (48 kHz sampling rate), not compatible with versions before v1.7.4.

  * YES: Enable full-band codec.
  * NO: Disable full-band codec.
 @param stereo Stereo codec, not compatible with versions before v1.7.4.

  * YES: Enable stereo codec.
  * NO: Disable stereo codec.
 @param fullBitrate High bitrate. Recommended in voice-only mode.

  * YES: Enable high bitrate mode.
  * NO: Disable high bitrate mode.
 @return * 0: Success.
 * < 0: Failure.
 */
- (int)setHighQualityAudioParametersWithFullband:(BOOL)fullband
                                          stereo:(BOOL)stereo
                                     fullBitrate:(BOOL)fullBitrate __deprecated_msg("use setAudioProfile:scenario: instead.");

#if (!(TARGET_OS_IPHONE) && (TARGET_OS_MAC))
/** Sets the speakerphone volume.

 **DEPRECATED** from v2.3.

 Note: This method applies to macOS only, not to iOS.

 @see [setDeviceVolume](setDeviceVolume:volume:).
 @param volume 0 (lowest volume) to 255 (highest volume).

 @return * 0: Success. * < 0: Failure.
 */
- (int)setSpeakerphoneVolume:(NSUInteger)volume __deprecated_msg("use setDeviceVolume:volume: instead.");
#endif

/** Sets the video encoding profile.

 **DEPRECATED** from v2.3.

 Each video encoding profile includes a set of parameters, such as the resolution, frame rate, and bitrate. If the camera device does not support the specified resolution, the SDK will automatically choose a suitable camera resolution, keeping the encoder resolution specified by setVideoProfile.

 Note:

 * Always set the video profile after calling the [enableVideo](enableVideo) method.
 * Always set the video profile before calling the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) or [startPreview](startPreview) method.
 * If you do set the video profile after joining the channel, call this method before enableVideo to shorten the time of the first frame showing.

 @see [setVideoEncoderConfiguration](setVideoEncoderConfiguration:)
 @param profile    Video profile: AgoraVideoProfile.
 @param swapWidthAndHeight Width and height of the output video, consistent with the set video profile. This parameter sets whether to swap the width and height of the stream:

 * YES: Swap the width and height. The video will be in portrait mode.
 * NO: (Default) Do not swap the width and height. The video remains in landscape mode.

 @return * 0: Success. * < 0: Failure.
 */
- (int)setVideoProfile:(AgoraVideoProfile)profile
    swapWidthAndHeight:(BOOL)swapWidthAndHeight __deprecated_msg("use setVideoEncoderConfiguration: instead.");

/** Sets the video encoding profile manually.

 **DEPRECATED** from v2.3.

 If you do not need to change the video profile after joining the channel, Agora recommends calling this method before enableVideo to shorten the time of the first frame showing.

 @see setVideoEncoderConfiguration:
 @param size      Size of the video. The highest value is 1280 &times; 720.
 @param frameRate Frame rate of the video. The highest value is 30. You can set it to 5, 10, 15, 24, 30, and so on.
 @param bitrate   Bitrate of the video. You need to manually work out the frame rate according to the width, height, and frame rate, see the bitrate table in AgoraVideoEncoderConfiguration. With the same width and height, the bitrate varies with the change of the frame rate:

 * If the frame rate is 5 fps, divide the recommended bitrate by 2.
 * If the frame rate is 15 fps, use the recommended bitrate.
 * If the frame rate is 30 fps, multiply the recommended bitrate by 1.5.
 * Calculate your bitrate with the ratio if you choose other frame rates.

 For example, the resolution is 320 &times; 240 and the frame rate is 15 fps, hence, the bitrate is 200:

 * If the frame rate is 5 fps, the bitrate is 100.
 * If the frame rate is 30 fps, the bitrate is 300.
 * If the bitrate you set is beyond the proper range, the SDK will automatically adjust it to a value within the range.
 */
- (int)setVideoResolution:(CGSize)size andFrameRate:(NSInteger)frameRate bitrate:(NSInteger)bitrate __deprecated_msg("use setVideoEncoderConfiguration: instead.");

/** Configures the CDN live streaming before joining a channel.

 **DEPRECATED**

 This method is deprecated. Agora recommends using the following methods instead:

 * [addPublishStreamUrl](addInjectStreamUrl:config:)
 * [removePublishStreamUrl](removeInjectStreamUrl:)
 * [setLiveTranscoding](setLiveTranscoding:)

 @param config CDN live streaming settings: AgoraPublisherConfiguration

 */
- (int)configPublisher:(AgoraPublisherConfiguration * _Nonnull)config __deprecated;

/** Sets the picture-in-picture layout for the CDN live broadcast.

 **DEPRECATED**

This method has been deprecated and Agora recommends using the [setLiveTranscoding](setLiveTranscoding:) method.

This method sets the picture-in-picture layouts for live broadcasts. This method is only applicable when you want to push streams to the Agora server. When you push the stream to the server:

 1. Define a canvas, its width and height (video resolution), background color, and the total number of video streams you want to display.
 2. Define the position and size for each video stream on the canvas, and indicate whether the view is cropped or zoomed to fit.

 The push stream application will format the information of the customized layouts as JSON and package it
 to the Supplemental Enhancement Information (SEI) of each keyframe when generating the H.264 video stream and pushing it to the CDN live vendors through the RTMP protocol.

 Note:

 - Call this method after joining a channel.
 - The app should only allow one user to call this method in the same channel. Call [clearVideoCompositingLayout]([AgoraRtcEngineKit clearVideoCompositingLayout]) to remove the settings.

 @see [setLiveTranscoding](setLiveTranscoding:)
 @param layout See AgoraRtcVideoCompositingLayout for details.

*/
- (int)setVideoCompositingLayout:(AgoraRtcVideoCompositingLayout * _Nonnull)layout __deprecated;

/** Removes the picture-in-picture layout settings.

 **DEPRECATED**

 Removes the picture-in-picture layout settings created by [setVideoCompositingLayout]([AgoraRtcEngineKit setVideoCompositingLayout:]).
 */
- (int)clearVideoCompositingLayout __deprecated;

/** Retrieves the device type; such as a recording, playback, or video capture device.

 **DEPRECATED**  from v2.3.

 Note: This method applies to macOS only, not to iOS.

 @see [getDeviceInfo](getDeviceInfo:).
 @param type Device type: AgoraMediaDeviceType
 @return When called successfully, it returns the device ID of the device. Otherwise, it returns nil.
 */
- (NSString * _Nullable)getDeviceId:(AgoraMediaDeviceType)type __deprecated_msg("use getDeviceInfo: instead.");

/** Plays the specified audio effect.

 **DEPRECATED** from v2.3.

 @see [playEffect](playEffect:filePath:loopCount:pitch:pan:gain:publish:)
 @param soundId ID of the audio effect. Each audio effect has a unique ID.
 Note: If you preloaded the audio effect into the memory through [preloadEffect]([AgoraRtcEngineKit preloadEffect:filePath:]), ensure that the soundID value is set to the same value as in preloadEffect.
 @param filePath Absolute path of the audio effect file.
 @param loopCount Number of times looping the audio effect:

 * 0: Play the audio effect once.
 * 1: Play the audio effect twice.
 * -1: Play the audio effect in an indefinite loop until [stopEffect]([AgoraRtcEngineKit stopEffect:]) or [stopAllEffects]([AgoraRtcEngineKit stopAllEffects]) is called.

 @param pitch Sets whether to change the pitch of the audio effect. The value ranges between 0.5 and 2.
 The default value is 1, which means no change to the pitch. The lower the value, the lower the pitch.
 @param pan Spatial position of the audio effect. The value ranges between -1.0 and 1.0.

 * 0.0: The audio effect displays ahead.
 * 1.0: The audio effect displays to the right.
 * -1.0: The audio effect displays to the left.

 @param gain Volume of the sound effect. The value ranges between 0.0 and 100.0 (default). The lower the value, the lower the volume of the sound effect.
 @return * 0: Success. * < 0: Failure.
 */
- (int)playEffect:(int)soundId
         filePath:(NSString * _Nullable)filePath
        loopCount:(int)loopCount
            pitch:(double)pitch
              pan:(double)pan
             gain:(double)gain __deprecated_msg("use playEffect:filePath:loopCount:pitch:pan:gain:publish: instead.");

/** Returns the Media Engine version.

 **DEPRECATED** from v2.3.

 @see getSdkVersion

 @return string, Media engine version
 */
+ (NSString * _Nonnull)getMediaEngineVersion __deprecated;


#pragma mark Deprecated Blocks

/**-----------------------------------------------------------------------------
 * @name Deprecated Blocks
 * -----------------------------------------------------------------------------
 */

/** Indicates who is talking and the speaker's volume.

 **DEPRECATED** from v1.1.

 This callback function is disabled by default and can be enabled by the [enableAudioVolumeIndication]([AgoraRtcEngineKit enableAudioVolumeIndication:smooth:]) method.

 In the returned speaker's array:

 * If the uid is 0 (the local user is the speaker), the returned volume is the totalVolume.
 * If the uid is not 0 and the volume is 0, the specified user did not speak.
 * If a uid is found in the previous speaker's array but not in the current speaker's array, the specified user did not speak.

@see [reportAudioVolumeIndicationOfSpeakers]([AgoraRtcEngineDelegate rtcEngine:reportAudioVolumeIndicationOfSpeakers:totalVolume:])

@param audioVolumeIndicationBlock This block includes:

- speakers: An array containing the user ID and volume information for each speaker.

   - uid: User ID of the speaker.
   - volume：Volume of the speaker. The value ranges between 0 (lowest volume) to 255 (highest volume).
- totalVolume: Total volume after audio mixing between 0 (lowest volume) to 255 (highest volume).
 */
- (void)audioVolumeIndicationBlock:(void(^ _Nullable)(NSArray * _Nonnull speakers, NSInteger totalVolume))audioVolumeIndicationBlock __deprecated_msg("use delegate instead.");

/** The first local video frame is rendered on the video window.

 **DEPRECATED** from v1.1.

 @see [firstLocalVideoFrameWithSize]([AgoraRtcEngineDelegate rtcEngine:firstLocalVideoFrameWithSize:elapsed:])

 @param firstLocalVideoFrameBlock This block includes:

 - width: Width (pixels) of the video stream.
 - height: Height (pixels) of the video stream.
 - elapsed: Time elapsed (ms) from the local user calling [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) until this callback function is triggered.
 */
- (void)firstLocalVideoFrameBlock:(void(^ _Nullable)(NSInteger width, NSInteger height, NSInteger elapsed))firstLocalVideoFrameBlock __deprecated_msg("use delegate instead.");

/** The first remote video frame has been received and decoded.

 **DEPRECATED** from v1.1.

 @see [firstRemoteVideoFrameOfUid]([AgoraRtcEngineDelegate rtcEngine:firstRemoteVideoFrameOfUid:size:elapsed:])

 @param firstRemoteVideoDecodedBlock This block includes:

 - uid:     User ID of the user sending the video streams.
 - width:   Width (pixels) of the video stream.
 - height:  Height (pixels) of the video stream.
 - elapsed: Time elapsed (ms) from the remote user calling [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) until this callback function is triggered.
 */
- (void)firstRemoteVideoDecodedBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoDecodedBlock __deprecated_msg("use delegate instead.");

/** The first remote video frame has been received and rendered.

 **DEPRECATED** from v1.1.

 @see [firstRemoteVideoDecodedOfUid]([AgoraRtcEngineDelegate rtcEngine:firstRemoteVideoDecodedOfUid:size:elapsed:])

 @param firstRemoteVideoFrameBlock This block includes:

 - uid:     User ID of the remote user sending the video streams.
 - width:   Width (pixels) of the video stream.
 - height:  Height (pixels) of the video stream.
 - elapsed: Time elapsed (ms) from the local user calling [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) until this callback function is triggered.
 */
- (void)firstRemoteVideoFrameBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger width, NSInteger height, NSInteger elapsed))firstRemoteVideoFrameBlock __deprecated_msg("use delegate instead.");

/** A user has joined the channel.

 **DEPRECATED** from v1.1.

 If there are other users in the channel when this user joins, the SDK also reports to the app on the existing users who are already in the channel.

 @see [didJoinedOfUid]([AgoraRtcEngineDelegate rtcEngine:didJoinedOfUid:elapsed:])

 @param userJoinedBlock This block includes:

 - uid:     User ID. If the uid is specified in the [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) method, it returns the specified ID. If the user ID is not specified when joinChannel is called, the server assigns one automatically.
 - elapsed: Time elapsed (ms) from the user calling  [joinChannelByToken](joinChannelByToken:channelId:info:uid:joinSuccess:) until this callback function is triggered.
 */
- (void)userJoinedBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger elapsed))userJoinedBlock __deprecated_msg("use delegate instead.");

/** A user has left the call or gone offline.

 **DEPRECATED** from v1.1.

 The SDK reads the timeout data to determine if a user has left the channel (or has gone offline). If no data package is received from the user in 15 seconds, the SDK assumes the user is offline. Sometimes a weak network connection may lead to false detections; therefore, Agora recommends using signaling for reliable offline detection.

 @see [didOfflineOfUid]([AgoraRtcEngineDelegate rtcEngine:didOfflineOfUid:reason:])
 @param userOfflineBlock This block includes: uid, the User ID.
 */
- (void)userOfflineBlock:(void(^ _Nullable)(NSUInteger uid))userOfflineBlock __deprecated_msg("use delegate instead.");

/** A remote user's audio stream has muted or unmuted.

 **DEPRECATED** from v1.1.

 @see [didAudioMuted]([AgoraRtcEngineDelegate rtcEngine:didAudioMuted:byUid:])

 @param userMuteAudioBlock This block includes:

 - uid:   ID of the remote user.
 - muted: Whether the remote user's audio stream has muted or unmuted:

     - YES: Muted.
     - NO: Unmuted.
 */
- (void)userMuteAudioBlock:(void(^ _Nullable)(NSUInteger uid, BOOL muted))userMuteAudioBlock __deprecated_msg("use delegate instead.");

/** A remote user's video stream has paused or resumed playing.

 **DEPRECATED** from v1.1.

 @see [didVideoMuted]([AgoraRtcEngineDelegate rtcEngine:didVideoMuted:byUid:])
 @param userMuteVideoBlock This block includes:

 - uid:   ID of the remote user.
 - muted: Whether the remote user's video has paused or resumed playing:

     - YES: Paused.
     - NO: Resumed.
 */
- (void)userMuteVideoBlock:(void(^ _Nullable)(NSUInteger uid, BOOL muted))userMuteVideoBlock __deprecated_msg("use delegate instead.");

/** The statistics of the uploading local video streams are reported once every two seconds.

 **DEPRECATED** from v1.1.

 @see [localVideoStats]([AgoraRtcEngineDelegate rtcEngine:localVideoStats:])
 @param localVideoStatBlock This block includes:

 - sentBitrate:  Bitrate sent since last count.
 - sentFrameRate: Frame rate sent since last count.
 */
- (void)localVideoStatBlock:(void(^ _Nullable)(NSInteger sentBitrate, NSInteger sentFrameRate))localVideoStatBlock __deprecated_msg("use delegate instead.");

/** The statistics of receiving remote video streams are reported once every two seconds.

 **DEPRECATED** from v1.1.

  @see [remoteVideoStats]([AgoraRtcEngineDelegate rtcEngine:remoteVideoStats:])

 @param remoteVideoStatBlock This block includes:

 - uid:                   User ID of the remote user sending the video streams.
 - delay:                 Time delay (ms).
 - receivedBitrate:       Bitrate received since last count.
 - receivedFrameRate:     Frame rate received since last count.
 */
- (void)remoteVideoStatBlock:(void(^ _Nullable)(NSUInteger uid, NSInteger delay, NSInteger receivedBitrate, NSInteger receivedFrameRate))remoteVideoStatBlock __deprecated_msg("use delegate instead.");

/** The camera is turned on and ready to capture the video.

 **DEPRECATED** from v1.1.

 @see [rtcEngineCameraDidReady]([AgoraRtcEngineDelegate rtcEngineCameraDidReady:])
 */
- (void)cameraReadyBlock:(void(^ _Nullable)(void))cameraReadyBlock __deprecated_msg("use delegate instead.");

/** The SDK has lost network connection with the server.

 **DEPRECATED** from v1.1.

 @see [rtcEngineConnectionDidInterrupted]([AgoraRtcEngineDelegate rtcEngineConnectionDidInterrupted:])
 @see [rtcEngineConnectionDidLost]([AgoraRtcEngineDelegate rtcEngineConnectionDidLost:])
 */
- (void)connectionLostBlock:(void(^ _Nullable)(void))connectionLostBlock __deprecated_msg("use delegate instead.");

/** When the client loses connection with the server because of network problems, the SDK automatically attempts to reconnect and triggers this callback function upon reconnection.

 **DEPRECATED** from v1.1.

 @see [didRejoinChannel]([AgoraRtcEngineDelegate rtcEngine:didRejoinChannel:withUid:elapsed:])
 @param rejoinChannelSuccessBlock This block includes:

 - channel: Channel name.
 - uid:     User ID.
 - elapsed: Time elapsed (ms) from starting to reconnect until this event occurs.
 */
- (void)rejoinChannelSuccessBlock:(void(^ _Nullable)(NSString * _Nonnull channel, NSUInteger uid, NSInteger elapsed))rejoinChannelSuccessBlock __deprecated_msg("use delegate instead.");

/** The RtcEngine runtime statistics reported once every two seconds.

 **DEPRECATED** from v1.1.

 @see [reportRtcStats]([AgoraRtcEngineDelegate rtcEngine:reportRtcStats:])
 @param rtcStatsBlock stat: see [AgoraChannelStats](AgoraChannelStats) for details.
 */
- (void)rtcStatsBlock:(void(^ _Nullable)(AgoraChannelStats * _Nonnull stat))rtcStatsBlock __deprecated_msg("use delegate instead.");

/** The user has left the channel.

 **DEPRECATED** from v1.1.

 When the app calls the [leaveChannel]([AgoraRtcEngineKit leaveChannel:]) method, the SDK uses this callback function to notify the app that the user has successfully left the channel.

 With this callback function, the app retrieves information, such as the call duration and the statistics of the data received/transmitted by [audioQualityOfUid]([AgoraRtcEngineDelegate rtcEngine:audioQualityOfUid:quality:delay:lost:]).

 @see [didLeaveChannelWithStats]([AgoraRtcEngineDelegate rtcEngine:didLeaveChannelWithStats:])
 @param leaveChannelBlock stat: see [AgoraChannelStats](AgoraChannelStats) for details.
 */
- (void)leaveChannelBlock:(void(^ _Nullable)(AgoraChannelStats * _Nonnull stat))leaveChannelBlock __deprecated_msg("use delegate instead.");

/** The audio quality of the current call is reported once every two seconds.

 **DEPRECATED** from v1.1.

 @see [audioQualityOfUid]([AgoraRtcEngineDelegate rtcEngine:audioQualityOfUid:quality:delay:lost:])
 @param audioQualityBlock This block includes:

 - uid:     User ID of the speaker
 - quality: Audio quality of the user: AgoraNetworkQuality
 - delay:   Time delay (ms)
 - lost:    Audio packet loss rate (%)
 */
- (void)audioQualityBlock:(void(^ _Nullable)(NSUInteger uid, AgoraNetworkQuality quality, NSUInteger delay, NSUInteger lost))audioQualityBlock __deprecated_msg("use delegate instead.");

/** The network quality of a specified user in a communication or live broadcast channel is reported once every two seconds.

 **DEPRECATED** from v1.1.

 @see [networkQuality]([AgoraRtcEngineDelegate rtcEngine:networkQuality:txQuality:rxQuality:])
 @param networkQualityBlock This block includes:

 - uid:       User ID. The network quality of the user with this UID will be reported. If uid is 0, the local network quality is reported.
 - txQuality: The transmission quality of the user: AgoraNetworkQuality
 - rxQuality: The receiving quality of the user: AgoraNetworkQuality
 */
- (void)networkQualityBlock:(void(^ _Nullable)(NSUInteger uid, AgoraNetworkQuality txQuality, AgoraNetworkQuality rxQuality))networkQualityBlock __deprecated_msg("use delegate instead.");

/** The last mile network quality of the local user.

 This callback function is triggered once every two seconds after [enableLastmileTest]([AgoraRtcEngineKit enableLastmileTest]) is called.

 **DEPRECATED** from v1.1.

 @param lastmileQualityBlock quality: Network quality, see [AgoraNetworkQuality](AgoraNetworkQuality) for details.
 */
- (void)lastmileQualityBlock:(void(^ _Nullable)(AgoraNetworkQuality quality))lastmileQualityBlock __deprecated_msg("use delegate instead.");

/** The media engine event.

 **DEPRECATED** from v1.1.
 */
- (void)mediaEngineEventBlock:(void(^ _Nullable)(NSInteger code))mediaEngineEventBlock __deprecated_msg("use delegate instead.");



@end
