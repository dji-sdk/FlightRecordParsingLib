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
            InvalidParameters,
            /// Illegal file content.
            IllegalFileContent,
            /// The file is not a supported version
            VersionNotSupport,
            /// No parser,
            NoParser,
            /// Feature not supported error.
            FeatureNotSupported,
            /// Decode failure due to some message lost.
            DecoderFailed,
            /// File operation failed.
            FileOperationFailed,
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
