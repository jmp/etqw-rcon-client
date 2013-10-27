etqw-rcon-client
================

This is a quick and dirty remote console client for the game "Enemy Territory:
Quake Wars" by Splash Damage. It can be used to remotely send commands to an
ETQW server. It is probably not much of use nowadays as the game is dead, but
it remains here in the hope that it will be useful for somebody.

compiling
---------

The program is written in ANSI C and I've tested it with TCC 0.9.25, GCC 4.3.2
and MSVC 15.0, but it might compile on others as well.

usage
-----

Run the program without arguments to see the parameters. The server must have
the net_ServerRemoteConsolePassword variable set before remote console can be
used:

	net_ServerRemoteConsolePassword "PASSWORD"

The server will respond with an error if the remote console is not enabled.
