#Tanks

About
-----

This game, which I programmed during the summer (2014) after my junior year
in high school, is a game in which the player controls a tank and battles
enemy tanks to advance. It has totally illogical physics.

I programmed the with C++ and SFML 2.1. I programmed the supporting
webpages with HTML, CSS, and JavaScript; I also used jQuery AJAX.

I borrowed some of the original versions of the files from the source code
of the book "SFML Game Development" by Artur Moreira, Henrik Vogelius
Hansson, and Jan Haller.

The following YouTube video contains a demonstration:
https://www.youtube.com/watch?v=Y1I0IGjln4U

Features
--------

This game includes tanks that can move and rotate, artificial intelligence,
collision detection, various enemies with different characteristics, data
for levels and tanks that is read from text files, and a state stack to
handle menus.

How to Run
----------

Download the project (perhaps from the releases section), unzip the folder,
open Tanks.sln with Microsoft Visual C++ 2012 Express (also known as
VS Express for Desktop), and run it (i.e. click "start debugging"). Note
that the SFML files, data text files, and media files are in the
repository.

There are webpages with supporting material under the directory
Tanks/Webpages. Note that I haven't implemented level guides, so the
link to the level guides doesn't work. Because the webpages import
a text file (with jQuery AJAX) that the user technically holds, Opera
and Chrome, neither of which supports allowing webpages to easily
get files from a client, can work with these webpages (unless something
like Web Server for Chrome is used). However, Safari, Internet Explorer,
and Firefox all work fine with the webpages.

Releases
--------

The most recent release is: v0.3

Check the releases tab of this repository on GitHub to download
the most recent version.

Authors
-------

That is me, Aaron Kaloti.

Known Problems
--------------

Should you happen to make your own edits, understand that having too
many enemies (and thus, too many bullets) causes the framerate to suffer
noticeably. I tried to experiment with fixing this problem, but I
decided to move on to different projects. However, the branches with
which I experimented with this problem (e.g. through means such as
recursive collision testing and quadtrees) still exist.

Contact Information
-------------------

My email address: aarons.7007@gmail.com

My YouTube channel (in which I demonstrate finished applications):
https://www.youtube.com/channel/UCHhcIcXErjijtAI9TWy7wNw/videos 