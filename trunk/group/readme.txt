Morse Texter 0.11

Dodgy prototype of Morse code input for texting.

 * Keys:
	Left arrow	Dot
	Right arrow	Dash
	OK key		Space

	1/4/7/*		Dot
	3/6/9/#		Dash
	2/5/8/0		Space

	C key		Delete last dot, dash, or letter

	Green/call key	Send as SMS

A single space ends the current Morse character and adds it to the normal text line. Subsequent spaces will add a space at the end of the normal text line.

 * Options->Send as SMS (same as green/call/dial key)
   When finished, use this to open the SMS editor with your text.

 * Options->Clear all
   Clears all dots, dashes, and text from the screen

 * Options->Morse code guide
   Open a guide showing the Morse code available. 
   Opened as a local html file in the browser.

Feel free to do whatever you want with this!


Ideas from:
http://www.russellbeattie.com/notebook/1008476.html
http://muddybranch.thejkgroup.com/2005/05/morse_code_trum.html
http://www.symbiandiaries.com/archives/gadget17/000954.html

Morse code from:
http://en.wikipedia.org/wiki/Morse_code

Some todos/ideas.
 * Add short and long key press handling on the OK key for dot and dash input, 
   with proper timing to add character and word spaces
 * Centre iMorseText and make it bigger/bolder
 * Some more ideas at http://www.symbiandiaries.com/archives/gadget17/000954.html
 * Vibrate 

Other interesting ideas I saw on the web!
 * "Ideally it'd be handy to be able to tap messages onto your mobile's case, 
    while it's in your pocket, and have that note saved on your device."
    http://www.markme.com/jd/archives/007833.cfm
 *  "Now, can we have an app to 'read' sms by vibrating please?  
    Then I can read and write them without looking ;-)"
    http://laivakoira.typepad.com/blog/2005/05/morse_texter.html and
    "This needs to be attached to the vibrate function. You could then recieve 
    messages without having to take it out of your pocket!"
    http://www.engadget.com/entry/1234000840045345/


Tested:
v0.06 reported working on 7610
v0.07 reported working on 7610, 6260
v0.08 reported working on 6680, 7610
v0.10 reported working on 7650, 7610, 6680

Known issues:
v0.06 - "It installs now on my 3620, but when I open the app it beeps and says "System error" then takes me back to the menu." Same reported on N-Gage. Not investigated the cause. 3620 and N-Gage are both Series 60 1.2 phones. Changed pkg file to only install on v2.0 or newer.
 -- fixed in v0.10 if built on 1.2 SDK
v0.10 - Selecting Exit a second time from Options menu doesn't work for some daft reason. 
        i.e. Options->Exit->No->Options->Exit->nowt happens.

New in 0.11:
 * Swap 'Morse code guide' and 'Sound on' in Options menu
 * Only launch html file if found
 * Dim 'Morse code guide' if html found
 * Show Morse in title pane (and removed iMorseText)
 * Show preview in navipane (and removed iPreviewText)
 * Show · instead of .
 * 'Clear all' shows instructions

New in 0.10:
 * Fixed typo in loc file ("1/4/6/0")
 * Removed unused tab
 * Build on 1.2 SDK - works on 7610, 6680 and 7650!
 * Added dit and dah sounds
 * Send Morse Texter to a friend via BT

New in 0.09:
 * There's not really any need for seperate "Delete dot or dash" and "Delete letter" 
   menu options, so I've removed them from the menu. Instead, the C key will delete 
   any dots/dashes first, and then will delete letters after that (as per 0.08).
 * Moved "Clear all" below "Send as SMS"

New in 0.08:
 * Assigned release UID from Symbian, so uninstall old one (otherwise you'll get two apps)
 * Install only for S60 v2.0 or newer
 * Swapped central and right column of numeric keys to match OK and rigt arrow
 * Added a Morse code guide
 * Added a confirmation query when exiting, so you don't lose your text by mistake
todo centre, big, bold
 * Tweaked C key to delete the last dot or dash if there is one, otherwise delete a letter
 * And added a preview of what you just entered


. /  -. / .--- / --- / -.-- / -·-·--

Hugo
20/08/2005

