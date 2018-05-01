# LEDs-to-voice
Voice activated accessible LEDs, also works with music

Hardware:
-arduino uno
-microphone amplifier with analog input (for arduino)
-5 meter NeoPixel strip LEDs (mine had 32 LED Diodes per meter)
  -I cut my 5 meter strip in 4, each having 38 diodes (not sure why instead of 40 diodes each...)
  
Setup:
  I then taped each of the four sections in an "X" shape on the wall. After connecting them to the arduino the code should produce a result where diodes will illumninate from the middle of the "X." Closer to the middle should be red, orange, yellow, progressing out to purple, blue, and light blue toward the edges of the X. 
  
Result:
  The louder the noise input the futher away from the middle of the "X" the LEDs are turned on.
