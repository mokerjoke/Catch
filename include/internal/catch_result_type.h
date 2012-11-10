/*
 *  Created by Phil on 07/01/2011.
 *  Copyright 2011 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_RESULT_TYPE_H_INCLUDED
#define TWOBLUECUBES_CATCH_RESULT_TYPE_H_INCLUDED

namespace Catch {    

    struct ResultWas { enum OfType {
        Unknown = -1,
        Ok = 0,
        Info = 1,
        Warning = 2,
        
        FailureBit = 0x10,
        
        ExpressionFailed = FailureBit | 1,
        ExplicitFailure = FailureBit | 2,
        
        Exception = 0x100 | FailureBit,
        
        ThrewException = Exception | 1,
        DidntThrowException = Exception | 2
        
    }; };

    inline bool isOk( ResultWas::OfType resultType ) {
        return ( resultType & ResultWas::FailureBit ) == 0;
    }

    struct ResultAction { enum Value {
        None,
        Failed = 1, // Failure - but no debug break if Debug bit not set
        Debug = 2,  // If this bit is set, invoke the debugger
        Abort = 4   // Test run should abort    
    }; };

    struct ResultDisposition {
        enum Flags {
            Normal = 0x00,

            ContinueOnFailure = 0x01,
            NegateResult = 0x02,
            SuppressFail = 0x04
        };
    };
    inline ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs ) {
        return static_cast<ResultDisposition::Flags>( static_cast<int>( lhs ) | static_cast<int>( rhs ) );
    }

    inline bool testFlag( int flags, int bitOrBitsToTest ) { return ( flags & bitOrBitsToTest ) == bitOrBitsToTest; }
    inline bool setFlag( int flags, int bitOrBitsToSet ) { return static_cast<ResultDisposition::Flags>( flags | bitOrBitsToSet ); }
    inline bool resetFlag( int flags, int bitOrBitsToReset ) { return static_cast<ResultDisposition::Flags>( flags & ~bitOrBitsToReset ); }

    inline bool shouldContinueOnFailure( int flags ) { return testFlag( flags, ResultDisposition::ContinueOnFailure ); }

} // end namespace Catch

#endif // TWOBLUECUBES_CATCH_RESULT_TYPE_H_INCLUDED
