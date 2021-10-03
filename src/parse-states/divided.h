#pragma once

#include <string>
#include "unparsed.h"

namespace TooReadable::ParseStates {

/** \class Divided divided.h "parse-states/divided.h"
 *  \brief <b>First stage of parsing:</b> divided to basic parts.
 */
class Divided
{
public:
    /**
     * Default constructor
     */
    Divided(Unparsed original);
};

}

#pragma once
