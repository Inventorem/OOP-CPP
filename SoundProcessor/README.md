# Task 3. Sound Processor

Sound processor for wav-files in PCM, 2 bytes samples

## **Effects:**
`mute start end 	`

`mix $n start 		//mix with given channel starting from start`

`clip start end		//Clip by given points`
## **Input format:**

`\> sound\_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]`

## **Configuration file format:**

#Comments</br>
#Start from new line</br>
mute 0 10\</br>
clip 0 20</br>
