//
// AgoraEnumerates.h
// AgoraRtcEngineKit
//
// Copyright (c) 2018 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Warning code.

Warning codes occur when the SDK encounters an error that may be recovered automatically. These are only notifications, and can generally be ignored. For example when the SDK loses connection with the server, the SDK will report the AgoraWarningCodeOpenChannelTimeout(106) code and try reconnecting automatically.
*/
typedef NS_ENUM(NSInteger, AgoraWarningCode) {
    /** The specified view is invalid. It is required to specify a view when using the video call function. */
    AgoraWarningCodeInvalidView = 8,
    /** Failed to initialize the video function, possibly caused by lack of resources. The users cannot see the video while the voice communication is not affected. */
    AgoraWarningCodeInitVideo = 16,
     /** The request is pending, usually due to some module not being ready, and the SDK postponed processing the request. */
    AgoraWarningCodePending = 20,
    /** No channel resources are available. Maybe because the server cannot allocate any channel resource. */
    AgoraWarningCodeNoAvailableChannel = 103,
    /** A timeout when looking up the channel. When joining a channel, the SDK looks up the specified channel. The warning usually occurs when the network condition is too poor to connect to the server. */
    AgoraWarningCodeLookupChannelTimeout = 104,
    /** The server rejected the request to look up the channel. The server cannot process this request or the request is illegal. */
    AgoraWarningCodeLookupChannelRejected = 105,
    /** The server rejected the request to look up the channel. The server cannot process this request or the request is illegal. */
    AgoraWarningCodeOpenChannelTimeout = 106,
    /** The server rejected the request to open the channel. The server cannot process this request or the request is illegal. */
    AgoraWarningCodeOpenChannelRejected = 107,
    /** A timeout when switching the live video. */
    AgoraWarningCodeSwitchLiveVideoTimeout = 111,
    /** A timeout when setting the client role in the broadcast mode. */
    AgoraWarningCodeSetClientRoleTimeout = 118,
    /** The client role is not authorized. */
    AgoraWarningCodeSetClientRoleNotAuthorized = 119,
    /** The ticket to open the channel is invalid. */
    AgoraWarningCodeOpenChannelInvalidTicket = 121,
    /** The client role is not authorized. */
    AgoraWarningCodeOpenChannelTryNextVos = 122,
    /** Error in opeinging the audio mixing. */
    AgoraWarningCodeAudioMixingOpenError = 701,
    /** Audio Device Module: A warning in the runtime playback device. */
    AgoraWarningCodeAdmRuntimePlayoutWarning = 1014,
    /** Audio Device Module: A warning in the runtime recording device. */
    AgoraWarningCodeAdmRuntimeRecordingWarning = 1016,
    /** Audio Device Module: No valid audio data is collected. */
    AgoraWarningCodeAdmRecordAudioSilence = 1019,
    /** Audio Device Module: A playback device failure. */
    AgoraWarningCodeAdmPlaybackMalfunction = 1020,
    /** Audio Device Module: A recording device failure. */
    AgoraWarningCodeAdmRecordMalfunction = 1021,
    /** The system interrupted the audio session, and the session is no longer active. */
    AgoraWarningCodeAdmInterruption = 1025,
    /** Audio Device Module: The recorded audio voice is too low. */
    AgoraWarningCodeAdmRecordAudioLowlevel = 1031,
    /** Audio Device Module: The playback audio voice is too low. */
    AgoraWarningCodeAdmPlayoutAudioLowlevel = 1032,
    /** Audio Device Module: Howling is detected. */
    AgoraWarningCodeApmHowling = 1051,
    /** Audio Device Module: The device is in the glitch state. */
    AgoraWarningCodeAdmGlitchState = 1052,
    /** Audio Device Module: The underlying audio settings have changed. */
    AgoraWarningCodeAdmImproperSettings = 1053,
};

/** Error code.

Error codes occur when the SDK encounters an error that cannot be recovered automatically without any application intervention. For example, the SDK reports the AgoraErrorCodeStartCall = 1002 error if it fails to start a call, and reminds the user to call [leaveChannel]([AgoraRtcEngineKit leaveChannel:]).
*/
typedef NS_ENUM(NSInteger, AgoraErrorCode) {
    /** No error. */
    AgoraErrorCodeNoError = 0,
    /** General error (the reason is not classified specifically). */
    AgoraErrorCodeFailed = 1,
    /** Invalid parameter called. For example, the specific channel name includes illegal characters. */
    AgoraErrorCodeInvalidArgument = 2,
    /** The SDK module is not ready.
     <p>Possible solutions：
     <ul><li>Check the state of the audio device.</li>
     <li>Check the completeness of the App.</li>
     <li>Try to re-initiate the SDK.</li></ul></p>
    */
    AgoraErrorCodeNotReady = 3,
    /** The current state of the SDK does not support this function. */
    AgoraErrorCodeNotSupported = 4,
    /** The request is rejected. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeRefused = 5,
    /** The buffer size is not big enough to store the returned data. */
    AgoraErrorCodeBufferTooSmall = 6,
    /** The SDK is not initialized before calling this API. */
    AgoraErrorCodeNotInitialized = 7,
    /** No permission. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeNoPermission = 9,
    /** An API timeout. Some APIs require the SDK to return the execution result, and this error occurs if the request takes too long (over 10 seconds) for the SDK to process. */
    AgoraErrorCodeTimedOut = 10,
    /** The request is cancelled. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeCanceled = 11,
    /** The call frequency is too high. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeTooOften = 12,
    /** The SDK failed to bind to the network socket. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeBindSocket = 13,
    /** The network is unavailable. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeNetDown = 14,
    /** No network buffers available. This is for internal SDK internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeNoBufs = 15,
    /** The request to join the channel is rejected.
     <p>The possible reasons are:
     <ul><li>The user is already in the channel, and still calls the API method to join the channel, for example, [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).</li>
     <li>The user tries joining the channel during the echo test. Please join the channel after the echo test.</li></ul></p>
    */
    AgoraErrorCodeJoinChannelRejected = 17,
    /** The request to leave the channel is rejected.
     <p>The possible reasons are:
     <ul><li>The user has already left the channel, and still calls the API method to leave the channel, for example, [leaveChannel]([AgoraRtcEngineKit leaveChannel:]).</li>
     <li>The user has not yet joined the channel, and calls the API method to leave the channel.</li></ul></p>
    */
    AgoraErrorCodeLeaveChannelRejected = 18,
    /** Resources are occupied and cannot be used. */
    AgoraErrorCodeAlreadyInUse = 19,
    /** The SDK gave up the request due to too many requests. This is for internal use only, and it will not return to the application through any API or callback event. */
    AgoraErrorCodeAbort = 20,
    /** In Windows, specific firewall settings can cause the SDK to fail to initialize and crash. */
    AgoraErrorCodeInitNetEngine = 21,
    /** The App has taken up too much of the system resources and the SDK has failed to allocate the resources. */
    AgoraErrorCodeResourceLimited = 22,
    /** The specified App ID is invalid. Please try to rejoin the channel with a valid App ID.*/
    AgoraErrorCodeInvalidAppId = 101,
    /** The specified channel name is invalid. Please try to rejoin the channel with a valid channel name. */
    AgoraErrorCodeInvalidChannelId = 102,
    /** The Token expired.
     <p>The possible reasons are:
     <ul><li>Authorized Timestamp expired: The timestamp is represented by the number of seconds elapsed since 1/1/1970. The user can use the Token to access the Agora service within five minutes after the Token is generated. If the user does not access the Agora service after five minutes, this Token will no longer be valid.</li>
     <li>Call Expiration Timestamp expired: The timestamp is the exact time when a party can no longer use the Agora service (for example, when someone is forced to leave an ongoing call). When the value is set for the Call Expiration Timestamp, it does not mean that the Token will be expired, but that the user will be kicked out of the channel.</li></ul></p>
     */
    AgoraErrorCodeTokenExpired = 109,
    /** The Token is invalid.
     <p>The possible reasons are:
     <ul><li>The App Certificate for the project is enabled on the Dashboard, but the user is still using the App ID. Once the App Certificate is enabled, the user must use a Token.</li>
     <li>The uid field is mandatory, and users must set the same uid when setting the uid parameter when calling [joinChannelByToken]([AgoraRtcEngineKit joinChannelByToken:channelId:info:uid:joinSuccess:]).</li></ul></p>
     */
    AgoraErrorCodeInvalidToken = 110,
    /** The internet connection is interrupted. This applies to the Agora Web SDK only. */
    AgoraErrorCodeConnectionInterrupted = 111,
    /** The internet connection is lost. This applies to the Agora Web SDK only. */
    AgoraErrorCodeConnectionLost = 112,
    /** 113: The user is not in the channel when calling the [sendStreamMessage]([AgoraRtcEngineKit sendStreamMessage:data:]) method. */
    AgoraErrorCodeNotInChannel = 113,
    /** 114: The size of the sent data is over 1024 bytes when the user calls the [sendStreamMessage]([AgoraRtcEngineKit sendStreamMessage:data:]) method. */
    AgoraErrorCodeSizeTooLarge = 114,
    /** 115: The bitrate of the sent data exceeds the limit of 6 Kbps when the user calls the [sendStreamMessage]([AgoraRtcEngineKit sendStreamMessage:data:]) method. */
    AgoraErrorCodeBitrateLimit = 115,
    /** 116: Too many data streams (over 5 streams) are created when the user calls the [createDataStream]([AgoraRtcEngineKit createDataStream:reliable:ordered:]) method. */
    AgoraErrorCodeTooManyDataStreams = 116,
    /** Decryption failed. The user may have used a different encryption password to join the channel. Please check your settings or try rejoining the channel. */
    AgoraErrorCodeDecryptionFailed = 120,
    /** Error in the watermark file parameter. */
    AgoraErrorCodeWatermarkParam = 124,
    /** Error in the watermark file path. */
    AgoraErrorCodeWatermarkPath = 125,
    /** Error in the watermark file format. */
    AgoraErrorCodeWatermarkPng = 126,
    /** Error in the watermark file information. */
    AgoraErrorCodeWatermarkInfo = 127,
    /** Error in the watermark file data format. */
    AgoraErrorCodeWatermarkAGRB = 128,
    /** Error in reading the watermark file. */
    AgoraErrorCodeWatermarkRead = 129,
    /** The encrypted stream is not allowed to publish. */
    AgoraErrorCodeEncryptedStreamNotAllowedPublish = 130,
    /** Stream publishing failed. */
    AgoraErrorCodePublishFailed = 150,
    /** Failed to load the media engine. */
    AgoraErrorCodeLoadMediaEngine = 1001,
    /** Failed to start the call after enabling the media engine. */
    AgoraErrorCodeStartCall = 1002,
    /** Failed to start the camera. */
    AgoraErrorCodeStartCamera = 1003,
    /** Failed to start the video rendering module. */
    AgoraErrorCodeStartVideoRender = 1004,
    /** General error on the Audio Device Module (the reason is not classified specifically). Please check if the audio device is used by other applications, or try joining the channel. */
    AgoraErrorCodeAdmGeneralError = 1005,
    /** Audio Device Module: Error in using the Java resources. */
    AgoraErrorCodeAdmJavaResource = 1006,
    /** Audio Device Module: Error in setting the sampling frequency. */
    AgoraErrorCodeAdmSampleRate = 1007,
    /** Audio Device Module: Error in initializing the playback device. */
    AgoraErrorCodeAdmInitPlayout = 1008,
    /** Audio Device Module: Error in starting the playback device. */
    AgoraErrorCodeAdmStartPlayout = 1009,
    /** Audio Device Module: Error in stopping the playback device. */
    AgoraErrorCodeAdmStopPlayout = 1010,
    /** Audio Device Module: Error in initializing the recording device. */
    AgoraErrorCodeAdmInitRecording = 1011,
    /** Audio Device Module: Error in starting the recording device. */
    AgoraErrorCodeAdmStartRecording = 1012,
    /** Audio Device Module: Error in stopping the recording device. */
    AgoraErrorCodeAdmStopRecording = 1013,
    /** Audio Device Module: Runtime playback error. Check the status of your playback device, or try rejoining the channel. */
    AgoraErrorCodeAdmRuntimePlayoutError = 1015,
    /** Audio Device Module: Runtime recording error. */
    AgoraErrorCodeAdmRuntimeRecordingError = 1017,
    /** Audio Device Module: Failed to record. */
    AgoraErrorCodeAdmRecordAudioFailed = 1018,
    /** Audio Device Module: Abnormal audio playback frequency. */
    AgoraErrorCodeAdmPlayAbnormalFrequency = 1020,
    /** Audio Device Module: Abnormal audio recording frequency. */
    AgoraErrorCodeAdmRecordAbnormalFrequency = 1021,
    /** Audio Device Module: Error in initializing the loopback device. */
    AgoraErrorCodeAdmInitLoopback  = 1022,
    /** Audio Device Module: Error in starting the loopback device. */
    AgoraErrorCodeAdmStartLoopback = 1023,
    /** No recording device. */
    AgoraErrorCodeAdmNoRecordingDevice = 1359,
    /** No playback device. */
    AgoraErrorCodeAdmNoPlayoutDevice = 1360,
    /** Video Device Module: The camera is not authorized. */
    AgoraErrorCodeVdmCameraNotAuthorized = 1501,
    /** Video Device Module: Unknown error. */
    AgoraErrorCodeVcmUnknownError = 1600,
    /** Video Device Module: Error in initializing the video encoder. */
    AgoraErrorCodeVcmEncoderInitError = 1601,
    /** Video Device Module: Error in video encoding. */
    AgoraErrorCodeVcmEncoderEncodeError = 1602,
    /** Video Device Module: Error in setting the video encoder.
    <p><b>DEPRECATED</b></p>
    */
    AgoraErrorCodeVcmEncoderSetError = 1603,
};

/** Video profile.

**DEPRECATED**

Please use AgoraVideoEncoderConfiguration.
*/
typedef NS_ENUM(NSInteger, AgoraVideoProfile) {
    /** Invalid profile. */
    AgoraVideoProfileInvalid = -1,
    /** Resolution 160 &times; 120, frame rate 15 fps, bitrate 65 Kbps. */
    AgoraVideoProfileLandscape120P = 0,
    /** Resolution 120 &times; 120, frame rate 15 fps, bitrate 50 Kbps. */
    AgoraVideoProfileLandscape120P_3 = 2, // iOS
    /** Resolution 320 &times; 180, frame rate 15 fps, bitrate 140 Kbps. */
    AgoraVideoProfileLandscape180P = 10, // iOS
    /** Resolution 180 &times; 180, frame rate 15 fps, bitrate 100 Kbps. */
    AgoraVideoProfileLandscape180P_3 = 12, // iOS
    /** Resolution 240 &times; 180, frame rate 15 fps, bitrate 120 Kbps. */
    AgoraVideoProfileLandscape180P_4 = 13, // iOS
    /** Resolution 320 &times; 240, frame rate 15 fps, bitrate 200 Kbps. */
    AgoraVideoProfileLandscape240P = 20,
    /** Resolution 240 &times; 240, frame rate 15 fps, bitrate 140 Kbps. */
    AgoraVideoProfileLandscape240P_3 = 22, //iOS
    /** Resolution 424 &times; 240, frame rate 15 fps, bitrate 220 Kbps. */
    AgoraVideoProfileLandscape240P_4 = 23, // iOS
    /** Resolution 640 &times; 360, frame rate 15 fps, bitrate 400 Kbps. */
    AgoraVideoProfileLandscape360P = 30,
    /** Resolution 360 &times; 360, frame rate 15 fps, bitrate 260 Kbps. */
    AgoraVideoProfileLandscape360P_3 = 32, // iOS
    /** Resolution 640 &times; 360, frame rate 30 fps, bitrate 600 Kbps. */
    AgoraVideoProfileLandscape360P_4 = 33,
    /** Resolution 360 &times; 360, frame rate 30 fps, bitrate 400 Kbps. */
    AgoraVideoProfileLandscape360P_6 = 35,
    /** Resolution 480 &times; 360, frame rate 15 fps, bitrate 320 Kbps. */
    AgoraVideoProfileLandscape360P_7 = 36,
    /** Resolution 480 &times; 360, frame rate 30 fps, bitrate 490 Kbps. */
    AgoraVideoProfileLandscape360P_8 = 37,
    /** Resolution 640 &times; 360, frame rate 15 fps, bitrate 800 Kbps.

     Note: This profile applies to the live broadcast channel profile only.
     */
    AgoraVideoProfileLandscape360P_9 = 38,
    /** Resolution 640 &times; 360, frame rate 24 fps, bitrate 800 Kbps.

     Note: This profile applies to the live broadcast channel profile only.
     */
    AgoraVideoProfileLandscape360P_10 = 39,
    /** Resolution 640 &times; 360, frame rate 24 fps, bitrate 1000 Kbps.

     Note: This profile applies to the live broadcast channel profile only.
     */
    AgoraVideoProfileLandscape360P_11 = 100,
    /** Resolution 640 &times; 480, frame rate 15 fps, bitrate 500 Kbps. */
    AgoraVideoProfileLandscape480P = 40,
    /** Resolution 480 &times; 480, frame rate 15 fps, bitrate 400 Kbps. */
    AgoraVideoProfileLandscape480P_3 = 42, // iOS
    /** Resolution 640 &times; 480, frame rate 30 fps, bitrate 750 Kbps. */
    AgoraVideoProfileLandscape480P_4 = 43,
    /** Resolution 480 &times; 480, frame rate 30 fps, bitrate 600 Kbps. */
    AgoraVideoProfileLandscape480P_6 = 45,
    /** Resolution 848 &times; 480, frame rate 15 fps, bitrate 610 Kbps. */
    AgoraVideoProfileLandscape480P_8 = 47,
    /** Resolution 848 &times; 480, frame rate 30 fps, bitrate 930 Kbps. */
    AgoraVideoProfileLandscape480P_9 = 48,
    /** Resolution 640 &times; 480, frame rate 10 fps, bitrate 400 Kbps. */
    AgoraVideoProfileLandscape480P_10 = 49,
    /** Resolution 1280 &times; 720, frame rate 15 fps, bitrate 1130 Kbps. */
    AgoraVideoProfileLandscape720P = 50,
    /** Resolution 1280 &times; 720, frame rate 30 fps, bitrate 1710 Kbps. */
    AgoraVideoProfileLandscape720P_3 = 52,
    /** Resolution 960 &times; 720, frame rate 15 fps, bitrate 910 Kbps. */
    AgoraVideoProfileLandscape720P_5 = 54,
    /** Resolution 960 &times; 720, frame rate 30 fps, bitrate 1380 Kbps. */
    AgoraVideoProfileLandscape720P_6 = 55,
    /** Resolution 1920 &times; 1080, frame rate 15 fps, bitrate 2080 Kbps. */
    AgoraVideoProfileLandscape1080P = 60,
    /** Resolution 1920 &times; 1080, frame rate 30 fps, bitrate 3150 Kbps. */
    AgoraVideoProfileLandscape1080P_3 = 62,
    /** Resolution 1920 &times; 1080, frame rate 60 fps, bitrate 4780 Kbps. */
    AgoraVideoProfileLandscape1080P_5 = 64,
    /** Resolution 2560 &times; 1440, frame rate 30 fps, bitrate 4850 Kbps. */
    AgoraVideoProfileLandscape1440P = 66,
    /** Resolution 2560 &times; 1440, frame rate 60 fps, bitrate 6500 Kbps. */
    AgoraVideoProfileLandscape1440P_2 = 67,
    /** Resolution 3840 &times; 2160, frame rate 30 fps, bitrate 6500 Kbps. */
    AgoraVideoProfileLandscape4K = 70,
    /** Resolution 3840 &times; 2160, frame rate 60 fps, bitrate 6500 Kbps. */
    AgoraVideoProfileLandscape4K_3 = 72,

    /** Resolution 120 &times; 160, frame rate 15 fps, bitrate 65 Kbps. */
    AgoraVideoProfilePortrait120P = 1000,
    /** Resolution 120 &times; 120, frame rate 15 fps, bitrate 50 Kbps. */
    AgoraVideoProfilePortrait120P_3 = 1002, //iOS
    /** Resolution 180 &times; 320, frame rate 15 fps, bitrate 140 Kbps. */
    AgoraVideoProfilePortrait180P = 1010, // iOS
    /** Resolution 180 &times; 180, frame rate 15 fps, bitrate 100 Kbps. */
    AgoraVideoProfilePortrait180P_3 = 1012, // iOS
    /** Resolution 180 &times; 240, frame rate 15 fps, bitrate 120 Kbps. */
    AgoraVideoProfilePortrait180P_4 = 1013, // iOS
    /** Resolution 240 &times; 320, frame rate 15 fps, bitrate 200 Kbps. */
    AgoraVideoProfilePortrait240P = 1020,
    /** Resolution 240 &times; 240, frame rate 15 fps, bitrate 140 Kbps. */
    AgoraVideoProfilePortrait240P_3 = 1022, // iOS
    /** Resolution 240 &times; 424, frame rate 15 fps, bitrate 220 Kbps. */
    AgoraVideoProfilePortrait240P_4 = 1023,
    /** Resolution 360 &times; 640, frame rate 15 fps, bitrate 400 Kbps. */
    AgoraVideoProfilePortrait360P = 1030, // iOS
    /** Resolution 360 &times; 360, frame rate 15 fps, bitrate 260 Kbps. */
    AgoraVideoProfilePortrait360P_3 = 1032, // iOS
    /** Resolution 360 &times; 640, frame rate 30 fps, bitrate 600 Kbps. */
    AgoraVideoProfilePortrait360P_4 = 1033,
    /** Resolution 360 &times; 360, frame rate 30 fps, bitrate 400 Kbps. */
    AgoraVideoProfilePortrait360P_6 = 1035,
    /** Resolution 360 &times; 480, frame rate 15 fps, bitrate 320 Kbps. */
    AgoraVideoProfilePortrait360P_7 = 1036,
    /** Resolution 360 &times; 480, frame rate 30 fps, bitrate 490 Kbps. */
    AgoraVideoProfilePortrait360P_8 = 1037,
    /** Resolution 360 &times; 640, frame rate 15 fps, bitrate 600 Kbps. */
    AgoraVideoProfilePortrait360P_9 = 1038,
    /** Resolution 360 &times; 640, frame rate 24 fps, bitrate 800 Kbps. */
    AgoraVideoProfilePortrait360P_10 = 1039,
    /** Resolution 360 &times; 640, frame rate 24 fps, bitrate 800 Kbps. */
    AgoraVideoProfilePortrait360P_11 = 1100,
    /** Resolution 480 &times; 640, frame rate 15 fps, bitrate 500 Kbps. */
    AgoraVideoProfilePortrait480P = 1040,
    /** Resolution 480 &times; 480, frame rate 15 fps, bitrate 400 Kbps. */
    AgoraVideoProfilePortrait480P_3 = 1042,    // iOS
    /** Resolution 480 &times; 640, frame rate 30 fps, bitrate 750 Kbps. */
    AgoraVideoProfilePortrait480P_4 = 1043,
    /** Resolution 480 &times; 480, frame rate 30 fps, bitrate 600 Kbps. */
    AgoraVideoProfilePortrait480P_6 = 1045,
    /** Resolution 480 &times; 848, frame rate 15 fps, bitrate 610 Kbps. */
    AgoraVideoProfilePortrait480P_8 = 1047,
    /** Resolution 480 &times; 848, frame rate 30 fps, bitrate 930 Kbps. */
    AgoraVideoProfilePortrait480P_9 = 1048,
    /** Resolution 480 &times; 640, frame rate 10 fps, bitrate 400 Kbps. */
    AgoraVideoProfilePortrait480P_10 = 1049,
    /** Resolution 720 &times; 1280, frame rate 15 fps, bitrate 1130 Kbps. */
    AgoraVideoProfilePortrait720P = 1050,
    /** Resolution 720 &times; 1280, frame rate 30 fps, bitrate 1710 Kbps. */
    AgoraVideoProfilePortrait720P_3 = 1052,
    /** Resolution 720 &times; 960, frame rate 15 fps, bitrate 910 Kbps. */
    AgoraVideoProfilePortrait720P_5 = 1054,
    /** Resolution 720 &times; 960, frame rate 30 fps, bitrate 1380 Kbps. */
    AgoraVideoProfilePortrait720P_6 = 1055,
    /** Resolution 1080 &times; 1920, frame rate 15 fps, bitrate 2080 Kbps. */
    AgoraVideoProfilePortrait1080P = 1060, // macOS
    /** Resolution 1080 &times; 1920, frame rate 30 fps, bitrate 3150 Kbps. */
    AgoraVideoProfilePortrait1080P_3 = 1062, // macOS
    /** Resolution 1080 &times; 1920, frame rate 60 fps, bitrate 4780 Kbps. */
    AgoraVideoProfilePortrait1080P_5 = 1064, // macOS
    /** Resolution 1440 &times; 2560, frame rate 30 fps, bitrate 4850 Kbps. */
    AgoraVideoProfilePortrait1440P = 1066, // macOS
    /** Resolution 1440 &times; 2560, frame rate 60 fps, bitrate 6500 Kbps. */
    AgoraVideoProfilePortrait1440P_2 = 1067, // macOS
    /** Resolution 2160 &times; 3840, frame rate 30 fps, bitrate 6500 Kbps. */
    AgoraVideoProfilePortrait4K = 1070, // macOS
    /** Resolution 2160 &times; 3840, frame rate 60 fps, bitrate 6500 Kbps. */
    AgoraVideoProfilePortrait4K_3 = 1072, // macOS
    /** (Default) Resolution 640 &times; 360, frame rate 15 fps, bitrate 400 Kbps. */
    AgoraVideoProfileDEFAULT = AgoraVideoProfileLandscape360P,
};

/** Video frame rate. */
typedef NS_ENUM(NSInteger, AgoraVideoFrameRate) {
    /** 1 fps. */
    AgoraVideoFrameRateFps1 = 1,
    /** 7 fps. */
    AgoraVideoFrameRateFps7 = 7,
    /** 10 fps. */
    AgoraVideoFrameRateFps10 = 10,
    /** 15 fps. */
    AgoraVideoFrameRateFps15 = 15,
    /** 24 fps. */
    AgoraVideoFrameRateFps24 = 24,
    /** 30 fps. */
    AgoraVideoFrameRateFps30 = 30,
    /** 60 fps. */
    AgoraVideoFrameRateFps60 = 60,
};

/** Video output orientation mode.

  Note: When a custom video source is used, if you set AgoraVideoOutputOrientationMode as AgoraVideoOutputOrientationModeFixedLandscape(1) or AgoraVideoOutputOrientationModeFixedPortrait(2), when the rotated video image has a different orientation than the specified output orientation, the video encoder will first crop it and then encode it.
 */
typedef NS_ENUM(NSInteger, AgoraVideoOutputOrientationMode) {
    /** Adaptive mode (Default).
     <p>The video encoder adapts to the orientation mode of the video input device. When a custom video source is used, the output video from the encoder inherits the orientation of the original video.
     <ul><li>If the width of the captured video from the SDK is larger than the height, the video sent out by the encoder is in landscape mode. The encoder also sends out the rotational information of the video, and the receiving end will rotate the received video based on the rotational information.</li>
     <li>If the original video is in portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends out the rotational information of the video to the receiver.</li></ul></p>
     */
    AgoraVideoOutputOrientationModeAdaptative = 0,
    /** Landscape mode.
     <p>The video encoder always sends out the video in landscape mode. The original video is rotated before being sent out and the rotational information is therefore 0. This mode applies to scenarios involving CDN live streaming.</p>
     */
    AgoraVideoOutputOrientationModeFixedLandscape = 1,
     /** Portrait mode.
      <p>The video encoder always sends out the video in portrait mode. The original video is rotated before being sent out and the rotational information is therefore 0. This mode applies to scenarios involving CDN live streaming.</p>
      */
    AgoraVideoOutputOrientationModeFixedPortrait = 2,
};

/** Channel profile. */
typedef NS_ENUM(NSInteger, AgoraChannelProfile) {
    /** Communication (default).
     <p>This is used in one-on-one or group calls, where all users in the channel can talk freely.</p>
     */
    AgoraChannelProfileCommunication = 0,
    /** Live Broadcast.
     <p>Host and audience roles that can be set by calling [setClientRole]([AgoraRtcEngineKit setClientRole:]). The host sends and receives voice/video, while the audience can only receive voice/video.</p>
     */
    AgoraChannelProfileLiveBroadcasting = 1,
    /** Gaming.
     <p>This mode is for the Agora Gaming SDK only.</p>
     <p>Any user in the channel can talk freely. This mode uses the codec with low-power consumption and low bitrate by default. </p>
     */
    AgoraChannelProfileGame = 2,
};

/** Client role in a live broadcast. */
typedef NS_ENUM(NSInteger, AgoraClientRole) {
    /** Host. */
    AgoraClientRoleBroadcaster = 1,
    /** Audience. */
    AgoraClientRoleAudience = 2,
};


/** Media type. */
typedef NS_ENUM(NSInteger, AgoraMediaType) {
    /** No audio and video. */
    AgoraMediaTypeNone = 0,
    /** Audio only. */
    AgoraMediaTypeAudioOnly = 1,
    /** Video only. */
    AgoraMediaTypeVideoOnly = 2,
    /** Audio and video. */
    AgoraMediaTypeAudioAndVideo = 3,
};


/** Encryption mode.

When encryptionMode is set NULL, the encryption mode is set to 128-bit AES encryption, XTS mode by default.
*/
typedef NS_ENUM(NSInteger, AgoraEncryptionMode) {
    AgoraEncryptionModeNone = 0,
    /** 128-bit AES encryption, XTS mode. */
    AgoraEncryptionModeAES128XTS = 1,
    /** 256-bit AES encryption, XTS mode. */
    AgoraEncryptionModeAES256XTS = 2,
    /** 128-bit AES encryption, ECB mode. */
    AgoraEncryptionModeAES128ECB = 3,
};

/** Reason for the user being offline. */
typedef NS_ENUM(NSUInteger, AgoraUserOfflineReason) {
    /** A user has quit the call. */
    AgoraUserOfflineReasonQuit = 0,
    /** The SDK timed out and the user dropped offline because it has not received any data package within a certain period of time. If a user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the user has dropped offline. */
    AgoraUserOfflineReasonDropped = 1,
    /** The user switched to an audience. */
    AgoraUserOfflineReasonBecomeAudience = 2,
};

/** Status of importing an external video stream in a live broadcast. */
typedef NS_ENUM(NSUInteger, AgoraInjectStreamStatus) {
    /** The external video stream imported successfully. */
    AgoraInjectStreamStatusStartSuccess = 0,
    /** The external video stream already exists. */
    AgoraInjectStreamStatusStartAlreadyExists = 1,
    /** The external video stream import is unauthorized. */
    AgoraInjectStreamStatusStartUnauthorized = 2,
    /** Import external video stream timeout. */
    AgoraInjectStreamStatusStartTimedout = 3,
    /** The external video stream failed to import. */
    AgoraInjectStreamStatusStartFailed = 4,
    /** The xternal video stream imports successfully. */
    AgoraInjectStreamStatusStopSuccess = 5,
    /** No external video stream is found. */
    AgoraInjectStreamStatusStopNotFound = 6,
    /** The external video stream is stopped from being unauthorized. */
    AgoraInjectStreamStatusStopUnauthorized = 7,
    /** Importing the external video stream timeout. */
    AgoraInjectStreamStatusStopTimedout = 8,
    /** Importing the external video stream failed. */
    AgoraInjectStreamStatusStopFailed = 9,
    /** The external video stream import is interrupted. */
    AgoraInjectStreamStatusBroken = 10,
};

/** Output log filter level. */
typedef NS_ENUM(NSUInteger, AgoraLogFilter) {
    /** Do not output any log information. */
    AgoraLogFilterOff = 0,
    /** Output all API log information. */
    AgoraLogFilterDebug = 0x080f,
    /** Output CRITICAL, ERROR, WARNING, and INFO level log information. */
    AgoraLogFilterInfo = 0x000f,
    /** Outputs CRITICAL, ERROR, and WARNING level log information. */
    AgoraLogFilterWarning = 0x000e,
    /** Outputs CRITICAL and ERROR level log information. */
    AgoraLogFilterError = 0x000c,
    /** Outputs CRITICAL level log information. */
    AgoraLogFilterCritical = 0x0008,
};

/** Audio recording quality. */
typedef NS_ENUM(NSInteger, AgoraAudioRecordingQuality) {
   /** Low quality, file size around 1.2 MB after 10 minutes of recording. */
    AgoraAudioRecordingQualityLow = 0,
    /** Medium quality, file size around 2 MB after 10 minutes of recording. */
    AgoraAudioRecordingQualityMedium = 1,
    /** High quality, file size around 3.75 MB after 10 minutes of recording. */
    AgoraAudioRecordingQualityHigh = 2
};

/** Lifecycle of the CDN live video stream.

**DEPRECATED**
*/
typedef NS_ENUM(NSInteger, AgoraRtmpStreamLifeCycle) {
    /** Bound to the channel lifecycle. If all hosts leave the channel, the CDN live streaming stops after 30 seconds. */
    AgoraRtmpStreamLifeCycleBindToChannel = 1,
    /** Bound to the owner of the RTMP stream. If the owner leaves the channel, the CDN live streaming stops immediately. */
    AgoraRtmpStreamLifeCycleBindToOwnner = 2,
};

/** Network quality. */
typedef NS_ENUM(NSUInteger, AgoraNetworkQuality) {
    /** The network quality is unknown. */
    AgoraNetworkQualityUnknown = 0,
    /**  The network quality is excellent. */
    AgoraNetworkQualityExcellent = 1,
    /** The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    AgoraNetworkQualityGood = 2,
    /** Users can feel the communication slightly impaired. */
    AgoraNetworkQualityPoor = 3,
    /** Users can communicate only not very smoothly. */
    AgoraNetworkQualityBad = 4,
     /** The network is so bad that users can hardly communicate. */
    AgoraNetworkQualityVBad = 5,
     /** The network is down  and users cannot communicate at all. */
    AgoraNetworkQualityDown = 6,
};

/** Video stream type. */
typedef NS_ENUM(NSInteger, AgoraVideoStreamType) {
    /** High-bitrate, high-resolution video stream. */
    AgoraVideoStreamTypeHigh = 0,
    /** Low-bitrate, low-resolution video stream. */
    AgoraVideoStreamTypeLow = 1,
};

/** Video display mode. */
typedef NS_ENUM(NSUInteger, AgoraVideoRenderMode) {
    /** Hidden(1): Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents. */
    AgoraVideoRenderModeHidden = 1,

    /** Fit(2): Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to the disparity in the aspect ratio will be filled with black. */
    AgoraVideoRenderModeFit = 2,

    /**
     Adaptive(3)：This mode is deprecated.
     */
    AgoraVideoRenderModeAdaptive __deprecated_enum_msg("AgoraVideoRenderModeAdaptive is deprecated.") = 3,
};

/** Self-defined video codec profile. */
typedef NS_ENUM(NSInteger, AgoraVideoCodecProfileType) {
    /** 66: Baseline video codec profile. Generally used in video calls on mobile phones. */
    AgoraVideoCodecProfileTypeBaseLine = 66,
    /** 77: Main video codec profile. Generally used in mainstream electronics, such as MP4 players, portable video players, PSP, and iPads. */
    AgoraVideoCodecProfileTypeMain = 77,
    /** 100: (Default) High video codec profile. Generally used in high-resolution broadcasts or television. */
    AgoraVideoCodecProfileTypeHigh = 100
};

/** Video mirror mode. */
typedef NS_ENUM(NSUInteger, AgoraVideoMirrorMode) {
    /** Default mirror mode determined by the SDK. */
    AgoraVideoMirrorModeAuto = 0,
    /** Enable mirror mode. */
    AgoraVideoMirrorModeEnabled = 1,
    /** Disable mirror mode. */
    AgoraVideoMirrorModeDisabled = 2,
};

/** Remote video state. */
typedef NS_ENUM(NSUInteger, AgoraVideoRemoteState) {
    /** Remote video stopped playing. */
    AgoraVideoRemoteStateStopped = 0,
    /** Remote video is playing. */
    AgoraVideoRemoteStateRunning = 1,
    /** Remote video is frozen. */
    AgoraVideoRemoteStateFrozen = 2,
};

/** Stream fallback option. */
typedef NS_ENUM(NSInteger, AgoraStreamFallbackOptions) {
    /** No fallback operation for the local/remote stream when the uplink/downlink network condition is poor. The quality of the stream cannot be guaranteed. */
    AgoraStreamFallbackOptionDisabled = 0,
    /** Under poor downlink network conditions, the SDK will receive the low video stream (of lower resolution and lower bitrate). You can only set this option in [setRemoteSubscribeFallbackOption]([AgoraRtcEngineKit setRemoteSubscribeFallbackOption:]). Nothing happens when you set this in [setLocalPublishFallbackOption]([AgoraRtcEngineKit setLocalPublishFallbackOption:]). */
    AgoraStreamFallbackOptionVideoStreamLow = 1,
    /** Under poor uplink network conditions, the SDK will send audio only; under poor downlink network conditions, the SDK may receive the low video stream (of lower resolution and lower bitrate) first, but if the network still does not allow displaying the video, the SDK will receive audio only. */
    AgoraStreamFallbackOptionAudioOnly = 2,
};

/** Audio sampling rate. */
typedef NS_ENUM(NSInteger, AgoraAudioSampleRateType) {
    /** 32 kHz. */
    AgoraAudioSampleRateType32000 = 32000,
    /** 44.1 kHz. */
    AgoraAudioSampleRateType44100 = 44100,
    /** 48 kHz. */
    AgoraAudioSampleRateType48000 = 48000,
};

/** Audio profile. */
typedef NS_ENUM(NSInteger, AgoraAudioProfile) {
    /** Default audio profile. In the communication mode, the default value is 1; in the live-broadcast mode, the default value is 2. */
    AgoraAudioProfileDefault = 0,
    /** Sampling rate of 32 kHz, audio encoding, mono, and bitrate up to 18 Kbps. */
    AgoraAudioProfileSpeechStandard = 1,
    /** Sampling rate of 48 kHz, music encoding, mono, and bitrate up to 48 Kbps. */
    AgoraAudioProfileMusicStandard = 2,
    /** Sampling rate of 48 kHz, music encoding, stereo, and bitrate up to 56 Kbps. */
    AgoraAudioProfileMusicStandardStereo = 3,
    /** Sampling rate of 48 kHz, music encoding, mono, and bitrate up to 128 Kbps. */
    AgoraAudioProfileMusicHighQuality = 4,
    /** Sampling rate of 48 kHz, music encoding, stereo, and bitrate up to 192 Kbps. */
    AgoraAudioProfileMusicHighQualityStereo = 5,
};

/** Audio scenario. */
typedef NS_ENUM(NSInteger, AgoraAudioScenario) {
    /** Default. */
    AgoraAudioScenarioDefault = 0,
    /** Entertainment scenario that supports voice during gameplay. */
    AgoraAudioScenarioChatRoomEntertainment = 1,
    /** Education scenario that prioritizes fluency and stability. */
    AgoraAudioScenarioEducation = 2,
    /** Live gaming scenario that needs to enable the gaming audio effects  in the speaker mode in a live broadcast scenario. Choose this scenario if you wish to achieve high-fidelity music playback. */
    AgoraAudioScenarioGameStreaming = 3,
    /** Showroom scenario that optimizes the audio quality with professional external equipment. */
    AgoraAudioScenarioShowRoom = 4,
    /** Gaming scenario. */
    AgoraAudioScenarioChatRoomGaming = 5
};

/** Audio output routing. */
typedef NS_ENUM(NSInteger, AgoraAudioOutputRouting) {
    /** Default. */
    AgoraAudioOutputRoutingDefault = -1,
    /** Headset.*/
    AgoraAudioOutputRoutingHeadset = 0,
    /** Earpiece. */
    AgoraAudioOutputRoutingEarpiece = 1,
    /** Headset with no microphone. */
    AgoraAudioOutputRoutingHeadsetNoMic = 2,
    /** Speakerphone. */
    AgoraAudioOutputRoutingSpeakerphone = 3,
    /** Loudspeaker. */
    AgoraAudioOutputRoutingLoudspeaker = 4,
    /** Bluetooth headset. */
    AgoraAudioOutputRoutingHeadsetBluetooth = 5
};

/** Use mode of the onRecordAudioFrame callback. */
typedef NS_ENUM(NSInteger, AgoraAudioRawFrameOperationMode) {
    /** Read-only mode: Users only read the AudioFrame data without modifying anything. For example, when users acquire data with the Agora SDK then push the RTMP streams. */
    AgoraAudioRawFrameOperationModeReadOnly = 0,
    /** Write-only mode: Users replace the AudioFrame data with their own data and pass them to the SDK for encoding. For example, when users acquire data. */
    AgoraAudioRawFrameOperationModeWriteOnly = 1,
    /** Read and write mode: Users read the data from AudioFrame, modify it, and then play it. For example, when users have their own sound-effect processing module and do some voice pre-processing such as a voice change. */
    AgoraAudioRawFrameOperationModeReadWrite = 2,
};

/** Audio equalization band frequency. */
typedef NS_ENUM(NSInteger, AgoraAudioEqualizationBandFrequency) {
    /** 31 Hz. */
    AgoraAudioEqualizationBand31 = 0,
    /** 62 Hz. */
    AgoraAudioEqualizationBand62 = 1,
    /** 125 Hz. */
    AgoraAudioEqualizationBand125 = 2,
    /** 250 Hz. */
    AgoraAudioEqualizationBand250 = 3,
    /** 500 Hz */
    AgoraAudioEqualizationBand500 = 4,
    /** 1 kHz. */
    AgoraAudioEqualizationBand1K = 5,
    /** 2 kHz. */
    AgoraAudioEqualizationBand2K = 6,
    /** 4 kHz. */
    AgoraAudioEqualizationBand4K = 7,
    /** 8 kHz. */
    AgoraAudioEqualizationBand8K = 8,
    /** 16 kHz. */
    AgoraAudioEqualizationBand16K = 9,
};

/** Audio reverberation type. */
typedef NS_ENUM(NSInteger, AgoraAudioReverbType) {
    /** The level of the dry signal in dB. The value ranges between -20 and 10. */
    AgoraAudioReverbDryLevel = 0,
    /** The level of the early reflection signal (wet signal) in dB. The value ranges between -20 and 10. */
    AgoraAudioReverbWetLevel = 1,
    /** The room size of the reverberation. A larger romm size means a stronger reverberation. The value ranges between 0 and 100. */
    AgoraAudioReverbRoomSize = 2,
    /** The length of the initial delay of the wet signal (ms). The value range between 0 and 200. */
    AgoraAudioReverbWetDelay = 3,
     /** The reverberation time. The value ranges between 0 and 100. */
    AgoraAudioReverbStrength = 4,
};

/** Audio session restriction. */
typedef NS_OPTIONS(NSUInteger, AgoraAudioSessionOperationRestriction) {
    /** No restriction, the SDK has full control on the audio session operations. */
    AgoraAudioSessionOperationRestrictionNone              = 0,
    /** The SDK will not change the audio session category. */
    AgoraAudioSessionOperationRestrictionSetCategory       = 1,
    /** The SDK will not change any setting of the audio session (category, mode, categoryOptions). */
    AgoraAudioSessionOperationRestrictionConfigureSession  = 1 << 1,
    /** The SDK will keep the audio session active when leaving a channel. */
    AgoraAudioSessionOperationRestrictionDeactivateSession = 1 << 2,
    /** The SDK will not configure the audio session anymore. */
    AgoraAudioSessionOperationRestrictionAll               = 1 << 7
};

/** Media device type. */
typedef NS_ENUM(NSInteger, AgoraMediaDeviceType) {
    /** Unknown device. */
    AgoraMediaDeviceTypeAudioUnknown = -1,
    /** Audio recording device. */
    AgoraMediaDeviceTypeAudioRecording = 0,
    /** Audio playback device. */
    AgoraMediaDeviceTypeAudioPlayout = 1,
    /** Video render device. */
    AgoraMediaDeviceTypeVideoRender = 2,
    /** Video capture device. */
    AgoraMediaDeviceTypeVideoCapture = 3,
};
