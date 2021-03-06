# Setting up Eclipse for QMK Development

[Eclipse][1] is an open-source [Integrated Development Environment](https://en.wikipedia.org/wiki/Integrated_development_environment) (IDE) widely used for Java development, but with an extensible plugin system that allows to customize it for other languages and usages.

Using an IDE such as Eclipse provides many advantages over a plain text editor, such as:
* intelligent code completion
* convenient navigation in the code
* refactoring tools
* build automation (no need for the command-line)
* a GUI for GIT
* static code analysis
* many other tools such as debugging, code formatting, showing call hierarchies etc.

The purpose of the is page is to document how to set-up Eclipse for developing AVR software, and working on the QMK code base.

Note that this set-up has been tested on Ubuntu 16.04 only for the moment.

# Prerequisites
## Build Environment
Before starting, you must have followed the [Getting Started](newbs_getting_started.md) section of the Tutorial. In particular, you must have been able to build the firmware with [the `qmk compile` command](newbs_building_firmware.md#build-your-firmware).

## Java
Eclipse is a Java application, so you will need to install Java 8 or more recent to be able to run it. You may choose between the JRE or the JDK, the latter being useful if you intend to do Java development.

# Install Eclipse and Its Plugins
Eclipse comes in [several flavours](https://www.eclipse.org/downloads/eclipse-packages/) depending on the target usage that you will have. There is no package comprising the AVR stack, so we will need to start from Eclipse CDT (C/C++ Development Tooling) and install the necessary plugins.

## Download and Install Eclipse CDT
If you already have Eclipse CDT on your system, you can skip this step. However it is advised to keep it up-to-date for better support.

If you have another Eclipse package installed, it is normally possible to [install the CDT plugin over it](https://eclipse.org/cdt/downloads.php). However it is probably better to reinstall it from scratch to keep it light and avoid the clutter of tools that you don't need for the projects you will be working on.

Installation is very simple: follow the [5 Steps to Install Eclipse](https://eclipse.org/downloads/eclipse-packages/?show_instructions=TRUE), and choose **Eclipse IDE for C/C++ Developers** at Step 3.

Alternatively, you can also directly [download Eclipse IDE for C/C++ Developers](https://www.eclipse.org/downloads/eclipse-packages/) ([direct link to current version](https://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/neonr)) and extract the package to the location of your choice (this creates an `eclipse` folder).

## First Launch
When installation is complete, click the <kbd>Launch</kbd> button. (If you extracted the package manually, open the Eclipse installation folder and double-click the `eclipse` executable)

When you are prompted with the Workspace Selector, select a directory that will hold Eclipse metadata and usually your projects. **Do not select the `qmk_firmware` directory**, this will be the project directory. Select the parent folder instead, or another (preferably empty) folder of your choice (the default is fine if you do not use it yet).

Once started, click the <kbd>Workbench</kbd> button at the top right to switch to the workbench view (there is a also checkbox at the bottom to skip the welcome screen at startup).

## Install the Necessary Plugins
Note: you do not need to restart Eclipse after installing each plugin. Simply restart once all plugins are installed.

### [The AVR Plugin](https://avr-eclipse.sourceforge.net/)
This is the most important plugin as it will allow Eclipse to _understand_ AVR C code. Follow [the instructions for using the update site](https://avr-eclipse.sourceforge.net/wiki/index.php/Plugin_Download#Update_Site), and agree with the security warning for unsigned content.

### [ANSI Escape in Console](https://marketplace.eclipse.org/content/ansi-escape-console)
This plugin is necessary to properly display the colored build output generated by the QMK makefile.

1. Open <kbd><kbd>Help</kbd> > <kbd>Eclipse Marketplace???</kbd></kbd>
2. Search for _ANSI Escape in Console_
3. Click the <samp>Install</samp> button of the plugin
4. Follow the instructions and agree again with the security warning for unsigned content.

Once both plugins are installed, restart Eclipse as prompted.

# Configure Eclipse for QMK
## Importing the Project
1. Click <kbd><kbd>File</kbd> > <kbd>New</kbd> > <kbd>Makefile Project with Existing Code</kbd></kbd>
2. On the next screen:
  * Select the directory where you cloned the repository as _Existing Code Location_;
  * (Optional) Give a different name to the project??, e.g. _QMK_ or _Quantum_;
  * Select the _AVR-GCC Toolchain_;
  * Keep the rest as-is and click <kbd>Finish</kbd>

  ![Importing QMK in Eclipse](https://i.imgur.com/oHYR1yW.png)

3. The project will now be loaded and indexed. Its files can be browsed easily through the _Project Explorer_ on the left.

?? There might be issues for importing the project with a custom name. If it does not work properly, try leaving the default project name (i.e. the name of the directory, probably `qmk_firmware`).

## Build Your Keyboard
We will now configure a make target that cleans the project and builds the keymap of your choice.

1. On the right side of the screen, select the <kbd>Make Target</kbd> tab
2. Expand the folder structure to the keyboard of your choice, e.g. `qmk_firmware/keyboards/ergodox`
3. Right-click on the keyboard folder and select <kbd>New???</kbd> (or select the folder and click the <kbd>New Make Target</kbd> icon above the tree)
4. Choose a name for your build target, e.g. _clean \<your keymap\>_
5. Make Target: this is the arguments that you give to `make` when building from the command line. If your target name does not match these arguments, uncheck <kbd>Same as target name</kbd> and input the correct arguments, e.g. `clean <your keymap>`
6. Leave the other options checked and click <kbd>OK</kbd>. Your make target will now appear under the selected keyboard.
7. (Optional) Toggle the <kbd>Hide Empty Folders</kbd> icon button above the targets tree to only show your build target.
8. Double-click the build target you created to trigger a build.
9. Select the <kbd>Console</kbd> view at the bottom to view the running build.

  [1]: https://en.wikipedia.org/wiki/Eclipse_(software)
