#pragma once

#include <stdexcept>


namespace BioTracker {
namespace Core {

struct video_open_error : std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

struct file_not_found : std::invalid_argument {
    using std::invalid_argument::invalid_argument;
};

}
}