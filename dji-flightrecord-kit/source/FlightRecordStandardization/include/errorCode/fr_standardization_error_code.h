//
//  fr_standardization_error_code.h
//  FlightRecordStandardization
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef fr_standardization_error_code_h
#define fr_standardization_error_code_h

namespace DJIFR {
    namespace standardization {
        enum class SDKError {
            /// Success
            Success = 0,
            /// Parameters invalid error.
            InvalidParameters = 1,
            /// Illegal file content.
            IllegalFileContent = 2,
            /// The file is not a supported version
            VersionNotSupport = 3,
            /// No parser,
            NoParser = 4,
            /// Feature not supported error.
            FeatureNotSupported = 5,
            /// Decode failure due to some message lost.
            DecoderFailed = 6,
            /// File operation failed.
            FileOperationFailed = 7,
            /// File data contamination
            FileDataContamination = 8,
            /// There are two possible causes.
            /// 1. Failure to fill data occurs when
            /// 2. Throw unsupported data fill types into the fill function.
            DataFormatChecksumFailure = 9,
            /// Failure due to unknown cause.
            Failure = 255,
        };
    
        enum class ServerError {
            /// Success
            Success = 0,
            InvaidParameter = 1,
            NotPermission = 2,
            NetworkIsNotReachable = 3,
            ParserFailure = 4,
        };
    }
}

#endif /* fr_standardization_error_code_h */
