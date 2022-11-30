# Embedded AI Training,Audio Signal n-Classification,Benchmarking and Embedded C Deployment to stm32.
# EmbeddedAi_Stm32
Embedded Artificial Intelligence training, classification and deployment to stm32 board.

# Project Info:

This is demonstration of embedded ai and implementation of low power ai systems.We are doing this by using Nano-Edge Ai-Studio by ST micro-electronics and using their stm32 dev board.Here we are collecting audio sammple from sensors then training classifying,then deploying it on the board to have a single isolated low power system for audio sample detection.

pre-requistes Nano-Edge ai studio,stm32 dev board,arduino ide,audio sensor,usb-b,lcd-nokia 5110

# Steps:
1. Download and install Nano-Edge AI studio from https://stm32ai.st.com/download-nanoedgeai/ (trial licence can be obtained for 3 months)
2. Download and install arduino IDE.
3. Add extra library sources in arduino ide from preference options. https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
4. Open Boards Manager then download and install stm32 boards.
5. Setup your stm 32 and audio sensor circuit for collecting audio samples via COM serial.(Please refer to the code for understanding pin connections,data to A0)
6. Open Nano-Edge Ai studio and then click n-classifications > Start collecting different audio samples atleast upto 100 lines,better the samples better the accuracy. >cross check with the fft waveform >Benchmark your audio samples(cpu extensive task)(score above 90% is acceptable)>Emulate and check if your audio is being detected as your said class>Validate the dataset and then deploy and compile the file.
7. Copy the knowledge.h ,libneai.a,NanoEdgeAI.h to arduino library Nokia_5110_LCD_library,NanoEdgeAI folders.
8. Now you can upload the secondly attached code to your stm32 board.
