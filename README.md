
# Simple-Log

SimpleLog is a lightweight and easy-to-use logging library written in C++. It is designed to be simple to integrate into your application with no need for additional configuration or linking of `.lib` or `.dll` files. It supports logging messages at three levels: INFO, WARNING, and ERROR. Additionally, SimpleLog allows you to define custom logging behavior using lambda functions.

## Features

- **Logging Levels:** INFO, WARNING, ERROR.
- **No External Dependencies:** No need for `.lib` or `.dll` files; plug and play.
- **Custom Callbacks:** Define custom logging behavior with lambda functions.
- **Easy Integration:** Simple API for quick setup.

## Requirements

- C++11 or higher compiler.
- Standard C++ library.

## Usage

### Basic Initialization

```cpp
#include "SIMPLE-LOG.hpp"

int main() {
    Log LOG("example.log"/*file opening mode (default trunc)*/); // Define an example log file
    
    // Define a callback function that is called when the logging system tries to write an error message
    LOG.set_ERROR_Callback([](const std::string& msg) {
        std::cout << "ERROR: " << msg << std::endl;
    });

    // Use write(LogLevel, const std::string&) to write the message to the log file
    LOG.write(LogLevel::INFO, "This is an example information");
    LOG.write(LogLevel::WARNING, "This is an example warning");
    LOG.write(LogLevel::ERROR, "This is an example error"); // Output: ERROR: This is an example error

    // Use LOG.Close() or ~LOG() to close the file
    return 0;
}
```
## License

This project is licensed under the MCC BY-NC 4.0 License. See the `LICENSE` file for details.

## Contact

For any questions or further information, please contact:

- Email: [Bf_bug_Feedback@126.com](mailto:Bf_bug_Feedback@126.com)
**and don't forget send your PC System and source code.**

Thank you for using SimpleLog!