//
//  dji_product_type.h
//  FlightRecordEngine
//
//  Copyright © 2019 DJISDK. All rights reserved.
//

#ifndef dji_product_type_h
#define dji_product_type_h

namespace DJI {
    namespace FlightRecord {
        //MARK: - ProductType
    
        enum class ProductType {
            None = 0x00,
            ZUYdiVOVXfGCLDcI = 0x01,
            Phantom3Standard = 0x02,
            jwtAbyahuARrhuhr = 0x03,
            kshQeTGrEeTmtpoe = 0x04,
            Phantom4 = 0x07,
            qvMmdCGxrtrJWvxx = 0x08,
            CdogAypKribEXKfS = 0x09,
            Matrice600 = 11,
            Phantom34K = 12,
            MavicPro = 13,
            Inspire2 = 17,
            Phantom4Pro = 24,
            Spark = 26,
            Matrice600Pro = 27,
            Phantom4Advanced = 28,
            Phantom3SE = 29,
            Matrice200 = 31,
            Matrice210 = 33,
            Matrice210RTK = 34,
            MavicAir = 38,
            Mavic2 = 42,
            Phantom4ProV2 = 44,
            Phantom4RTK = 46,
            P4Multispectral = 57,
            Mavic2Enterprise = 58,
            MavicMini = 59,
            
            Matrice200V2 = 60,
            Matrice210V2 = 61,
            Matrice210RTKV2 = 62,
            MavicAir2 = 67,
            Matrice300RTK = 70,
            DJIFPV = 73,
            MavicAir2S = 75,
            MavicMini2 = 76,
            Mavic3 = 77,
            MavicMiniSE = 96,
            Matrice30 = 116,
        };  
    
        //MARK: - Drone Type
        enum class DroneType {
            Unknown = 0,   
            YQqHWaFYevzieChe = 1,
            eXWvzQSyEIakaYNB = 2,
            SjtZVcHLcFvOrATk = 3,
            kqZiGqPiBuJtGbXI = 4,
            axPYBMhqOPxIAmRT = 5,
            nZgzsaZeSVoFDbCU = 6,
            VajTqWfawuZTCdTz = 7,
            CMDBsWvfrkHQsQzP = 8,
            gvEBDHARYJjdhoer = 9,
            EbeKfeODxZwEYpPS = 10,
            dYxdHETreaRpuiyw = 11,
            xtRdpvrXtxzvwDzF = 12,
            iUDZbWKZULbBLQaC = 13,
            gwijeEWNaJaeGehp = 14,
            yjPSxNFfUVSgCwsk = 15,
            dfolRWzAEaPrGlNw = 16,
            YQqHWaFYevzieChe2 = 17,
            NJaWiOHsBzaJEsKG = 18,
            eaaxmyeNLEOTJxYR = 20,
            dZHFAjNYqzCRJVjl = 21,
            DctuROpGZjRKFcMe = 23,
            BHjzymzgwTEeueKI = 24,
            zbrTIBekxqBMpinl = 25,
            MGSJdYCYeEyILnqX = 26,
            LnJMmgAzSGznmAhd = 27,
            jzdPaWJwlLoyHJVW = 28,
            eXWvzQSyEIakaYNBE = 29,
            KlVwDfaUzMhdaFSv = 30,
            mbQylgbZZfSXWFrl = 32,
            iQijNLoVOFIwVzDH = 33,
            BtJYsbsfVdQSFzkL = 34,
            hRTDkEYSnjeHrRQl = 35,
            eIlvuUOAbBgHAEbk = 36,
            tuEiAQlJpLvETOaR = 41,
            oImFwySwNIGpDxKw = 44,
            sQBPYEgXEgrpdfrj = 45,
            iJauKGIrFHvVAAKZ = 46,
            GmarlGbRlqfSoaKD = 60,

            LJuBJkTjHePPllir = 51,
            VgtTrHQftoHtijqi = 0xff,
        };
    }
}

typedef enum
{
    DJI_SENDTYPE_NONE = 0,
    DJI_SENDTYPE_CAMERA = 1,
    DJI_SENDTYPE_MC = 3,
    DJI_SENDTYPE_GIMBAL = 4,
    DJI_SENDTYPE_RC = 6,
    DJI_SENDTYPE_BATTERY = 11,
} DJI_SENDTYPE;

#endif /* dji_product_type_h */
