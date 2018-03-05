////////////////////////////////////////////////////////////////////////////
/////Space City CanSat - University of Houston CanSat Competition Team//////
/////Ground Control Software (GCSW) PROTOTYPE Version 0.2///////////////////
/////Author: Michael Greer//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

Description_________________________________________________________________

	As a part of competition requirements, the team has a need for a 
software package written for the Ground Control Station to receive, save 
and display telemetry data throughout mission operations. 

	This software prototype will be an evolving package to test 
capabilities to be implemented in the final GCSW package. 

	Versioning will be based on new capability implementation; when a 
new capability is added, version will be incremented by an integer value. 
Point versions will be added for capability refinement. Point-Point for tweaks. 

////PLANS////
V1: 
- Implement serial reading functionality to take serial data and print 
directly to a simple display GUI.
- Write the data being displayed to a .csv file
	- Data starts writing when a start button is pushed, stops when stop button is pushed. 
	- Input field for file name
- Have a serial setting dialogue to select port/port settings

Changenotes below.

ChangeNotes_________________________________________________________________

V0.2 _______________________________________________________________________

- Implemented simple serial reading capabilities. Not pretty but it works atm.
	- Data coming in at the serial line gets printed to the display
	- Need to manually select port by looking at debugger info

V0.1 (Initial) _____________________________________________________________

Initial version; simple print to GUI ("Hello World"). 



