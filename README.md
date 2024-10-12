# Nutshell

<img src="https://github.com/user-attachments/assets/d7a119fb-5a27-4282-b13b-a7ba6982695e" width=100/>


**Nutshell** is a shell that, in a nutshell, is a nutshell. It’s compact shell I am developing in C.

## Features

- **Command Execution**: Run basic shell commands with ease!
- **Argument Handling**: Pass arguments like a pro.

Future Support:
1. Piping
2. Background
3. Builtin
4. etc

## Build Instructions

Make sure to have the following dependencies:

- **Clang**: For compiling.
- **Flex**: To generate the lexical analyzer.
- **Bison**: Parser generator

### Steps to Build

1. **Install Dependencies**: First, ensure you have `clang`, `flex`, and `bison` installed. If you’re on a Ubuntu/Debian-based system, run:
   ```
   sudo apt update
   sudo apt install clang flex bison
   ```

2. **Clone the Repository**: Grab your very own Nutshell:
   ```
   git clone https://github.com/yourusername/nutshell.git
   cd nutshell
   ```

3. **Run the Build Script**: Let’s get cracking! Execute the build script to compile Nutshell:
   ```
   ./build.sh
   ```

## Usage

Welcome to Nutshell! Once you start it up, you’ll see a prompt waiting for your commands, like a squirrel eagerly awaiting its next nut. Here are some fun examples to try out:

- **List Files**: See what treasures lie in your directory:
   ```
   > ls
   ```

- **Sleep in the Background**: Let commands snooze while you do other things:
   ```
   > sleep 10
   ```

- **Piping Commands**: Combine commands like a clever squirrel stacking nuts:
   ```
   > ls | grep ".c"
   ```

## Contributing

Want to add your own flair to Nutshell? We’d love to have you! Feel free to fork the repository and submit a pull request. Let’s make this nutshell even nuttier!

## License

This project is licensed under the MIT License. Check out the [LICENSE](LICENSE) file for all the juicy details.

## Acknowledgments

- Special thanks to the creators of Clang, Flex, and Bison for providing the tools that make this shell possible. You’re the real MVPs in this nutshell!

---

You can copy and paste this text directly into your README file. The formatting will be preserved correctly when rendered in Markdown.
