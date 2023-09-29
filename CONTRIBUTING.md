# Contribution Guidelines

This game is a community driven effort to build a fun and growing community - your contributions are invaluable!

## Issues

The easiest way to contribute is by reporting issues. When reporting an issue, make sure to clearly state:

- The machine setup: "I'm using Windows 10 Anniversary Update. My machine is Visual Studio 2019."
- The steps to reproduce: "I ran 'CMake -B build'"
- The outcome you expected: "I expect 'build complete'"
- The actual outcome: "I get no output at all" or "I got a crash report"
- The revelant information about the issue: "Error Log from CMake"

## Pull Requests

We are happy to accept pull requests for fixes, features, and updates to existing code. In order to avoid wasting your time, we highly encourage opening an issue to discuss whether the PR you're thinking about making will be acceptable. This is doubly true for new features and fixes.

### New Features Guidelines

We're glad you're interested in submitting a new feature ! Here are some guidelines to help you author an excellent portfile:

- Try to have good behavior when coding, references, private functions, constant, ect.
- Follow code format from other files. For example, if you want to add a new component, don't forget the namespace before it, don't forget the define at the beginning of a header.
- Avoid specific features. If you want to add an extra feature, it has to be modular, for example, don't create an achievement, create a component obtainable to make achievements.
- Take a second to format your code with the .clang-format file given in the repository.

## Legal

You will need to complete a Contributor License Agreement (CLA) before your pull request can be accepted. This agreement testifies that you are granting us permission to use the source code you are submitting, and that this work is being submitted under appropriate license that we can use it.
