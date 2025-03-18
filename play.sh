#!/bin/bash

GREEN='\033[0;32m'
BLUE='\033[0;36m'
PURPLE='\033[1;35m'
YELLOW='\033[0;33m'
NORMAL='\033[0m'  # Define NORMAL as reset (in ASNI)

install_dependencies() {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        # macOS
        if ! command -v brew &> /dev/null; then
            echo -e "${YELLOW}Homebrew not found. Installing Homebrew...${NORMAL}"
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        fi
        
        echo -e "${PURPLE}Checking SDL2 dependencies...${NORMAL}"
        local brew_packages=("sdl2" "sdl2_ttf" "sdl2_mixer" "sdl2_image" "sdl2_net")
        local missing_packages=()

        for package in "${brew_packages[@]}"; do
            if ! brew list "$package" &> /dev/null; then
                missing_packages+=("$package")
            fi
        done

        if [ ${#missing_packages[@]} -ne 0 ]; then
            echo -e "${YELLOW}Installing missing dependencies: ${missing_packages[*]}${NORMAL}"
            brew install "${missing_packages[@]}"
        fi
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux
        echo -e "${PURPLE}Checking SDL2 dependencies...${NORMAL}"
        local apt_packages=("libsdl2-dev" "libsdl2-ttf-dev" "libsdl2-mixer-dev" "libsdl2-image-dev" "libsdl2-net-dev")
        
        if ! command -v apt-get &> /dev/null; then
            echo -e "${RED}Error: apt-get not found. Please install SDL2 dependencies manually.${NORMAL}"
            exit 1
        fi

        echo -e "${YELLOW}Installing SDL2 dependencies...${NORMAL}"
        sudo apt-get update
        sudo apt-get install -y "${apt_packages[@]}"
    else
        echo -e "${RED}Unsupported operating system${NORMAL}"
        exit 1
    fi
}

clear

# Check system requirements first
echo -e "${PURPLE}Checking system requirements...${NORMAL}"
install_dependencies

# Print a message to the user
echo -e "${BLUE}Welcome to the NEW Pong Game from Dounia Bakalem, Yanis Sadoun and Vasileios Filippos Skarleas. Once you are ready to start exploring the game simply by pressing ENTER"
echo -e "${GREEN}Bienvenue au jeu NEW Pong de Dounia Bakalem, Yanis Sadoun, Vasileios Filippos Skarleas. Une fois que vous êtes prêt à commencer à explorer les capacités du logiciel, appuyez simplement sur ENTRÉE."

# Read a line of input from the user
read input

# If the user presses Enter, run the specified commands
if [[ -n "$input" ]]; then
  echo -e "${PURPLE}You did not press ENTER and the program will terminate"
else
  # Run the initial commands
  clear
  echo -e "${PURPLE}Initialising environment..."
  sleep 2
  mkdir -p build
  cd build
  cmake ..
  cmake --build .
  clear
  ./Pong
  # echo -e "${NORMAL}This software allows you to play the pong game.\n"
  # echo -e "${BLUE}NOTE:${NORMAL} You have the option to play either on 2 or against an AI. More details about the game and its implimentation at https://github.com/vskarleas/ROB4-S8-Cpp_Project.\n"
  # echo -e "++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

  # # Infinite loop with user options
  # while true; do
  #   clear
  #   echo -e "\n- play: You can launch the game."
  #   echo -e "- exit: Exits the installer program."
  #   echo -e "${BLUE}========================================================\n${NORMAL}Enter a command (play, exit):"
  #   read command

  #   case "$command" in
  #     play)
  #       ./Pong
  #       ;;
  #     exit)
  #       break  # Exit the loop
  #       ;;
  #     *)
  #       echo -e "${YELLOW}\nInvalid command. Please try again!${NORMAL}"
  #       ;;
  #   esac
  # done

  # Commands to execute after exiting the loop
  echo -e "${GREEN}The NEW Pong Game has been successfully terminated\n"
  echo -e "${NORMAL}Thank you! | ${BLUE}Copyright © 2025 - $(date +%Y) ${NORMAL} Vasileios Filippos Skarleas, Yanis Sadoun, Dounia Bakalem - All rights reserved"
fi
