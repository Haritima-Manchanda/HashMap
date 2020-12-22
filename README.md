# HashMap
Hash Map Data Structure in C++

## Overview
For this project we used a word and a set of following words to generate text in a particular “voice”. By voice, I mean the patterns with which different authors use words. Every author has their own unique word patterns. For this example, we emulated Dr. Seuss’ voice and Charles Dickens’ voice. 

More specifically, we read in a text file of Dr. Seuss stories first and the first 2 chapters of Great Expectations. Each word read in was a key, and the values associated with each key was an array of Strings, or the set of words that follow a word. So, for instance, if you have the word “I” as your key, the array of values might be a list that would look like {“do”,”see”,”have”,”am”,”do”,”need”}, etc. The value that is associated with the key “I” is every word in the Dr. Seuss text that follows the word “I”.

So we read in the Dr. Seuss text and Charles Dickins text into a HashMap, with the keys being the words in the file, and the values associated with each key are the words that follow a particular word throughout the text. More specifically, the current word we read in is first added to the value set of the previous word we read in, which is the key. The current word then becomes the key and we read in the next word, which is the value of that word.
