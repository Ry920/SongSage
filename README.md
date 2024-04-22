<H1> COP3530 - Project 3 </h1>
SongSage - Tailored Tunes Just for You!

Ryan Brito, Emma Herrero, Ria Saldajeno.

For University of Florida, COP3530, Spring 2024.

Demo video link: https://youtu.be/0S48mjY4hgE

<h2> Instructions: </h2>
To run this program, download all files included in the repository. SFML will be downloaded by the CMake file as it is compiled. Compile the program, and SongSage will be ready for you.

<h2> About: </h2>
&emsp;How many times have you struggled to find the perfect song to match the mood you are feeling? While this may not be a life-endangering issue, it still is annoying to not have a song ready that perfectly matches the mood you are in. With SongSage, users can tell the program how energetic and how danceable they want their songs to be, and SongSage will find the five best matches perfectly curated for them.

<h2> Features: </h2>
&emsp;This program first displays a welcome screen for the users. The welcome screen displays the program’s name, tagline, and brief instructions for use. On this welcome screen, users have to choose three options for their customized song list. First, users must use the slider to indicate how “danceable” they want their songs to be. Users then use another slider to indicate how energetic they want their songs to be. Both of the sliders’ values correlate to a level between 1 in 0, depending on how far right or left the user decides to move the slider. Next, users can use the on/off switch on the far left of the screen to indicate whether or not they want their songs to include explicit language. By default, the danceability and energy are set to 0, and the explicit language is turned on. Users must select what type of sorting method they would like to use to generate their songs. If users attempt to hit the “next” arrow before their sporting type is selected, an error message will appear, prompting users to select a type of sorting method. Once the user selects the sorting type, it is bolded and underlined to ensure that the users can see their choice. Next, users click the next arrow and their songs are generated. 
While the users wait for their curated list to be generated, a “Loading” and “Sorting” animated screen is displayed. Finally, the results page is opened and lists the user’s top five song recommendations based on their input. The results page displays the sorting algorithm used to generate the list as well as the time (in milliseconds) it took for the program to generate the songs.

<h2> References: </h2>


- SFML (library and tutorials used): SFML Documentation (SFML / Learn / 2.6.1 Documentation) (sfml-dev.org)
- Song Dataset:  https://www.kaggle.com/datasets/maharshipandya/-spotify-tracks-dataset
- Fonts from: https://www.fontspace.com/category/ttf
- “setText” function from “Minesweeper”assignment created by Dr. Cruz Castro for COP3530, University of Florida, Summer 2023
- UTF-8 File Encodng: c++ - How to read an UTF-8 encoded file containing Chinese characters and output them correctly on console? - Stack Overflow
- Shell Sort Implementation: ShellSort - GeeksforGeeks
