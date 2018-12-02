# Morse Texter: Send an SMS using Morse code

![](images/4715_morsetexter002jpg.jpg) ![](images//4716_morsetexter003jpg.jpg)

![](images//4717_morsetexter004jpg.jpg) ![](images//4718_morsetexter006jpg.jpg)

After reading [this](http://www.russellbeattie.com/notebook/1008476.html) and [this](https://web.archive.org/web/20071013222028/http://muddybranch.thejkgroup.com:80/2005/05/morse_code_trum.html) and [this](http://www.m0tzo.co.uk/2004/01/11/morse-code-software/) I decided to knock up this dodgy prototype amazing application for S60 v2.x phones (but not v1.x or v3.x -- check your version [here](https://en.wikipedia.org/wiki/S60_(software_platform))). Tap in some Morse code, and then send it as an SMS. Keys are:

* 1, 4, 7, or * - Dot
* 2, 5, 8, or 0 - Space
* 3, 6, 9, or # - Dash
* Left arrow - Dot
* OK key - Space
* Right arrow - Dash
* C key - Delete last dot, dash or letter
* Call/green key - Send as SMS

For a gap between letters, press space once. For a gap between words, press space a second time.

Here's the source, do whatever you want with it. Some ideas:

* Port to S60 3rd Edition
* Add short and long key press handling on the OK key for dot and dash input, with proper timing to add character and word spaces
* Centre the Morse characters and make them bigger/bolder
* [More ideas](http://www.m0tzo.co.uk/2004/01/general/morse-code-software/)

. / -. / .--- / --- / -.-- / -.-.--
