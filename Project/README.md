# Phase 2: Chat Server
Project handled by team unity

---
### Table of Contents
- [Overview](#overview)
- [Running the Server](#running-the-server)
- [Additional Infomation](#additional-information)

---

## Overview

The aim of this project is to develop a real-time client/server chat application that may be run in a linux enviroment. 

---

## Running the Server

To run the server, the following command must first be run


	>> 	./client <Server IP> <Server Port> <username>


Once the server has been accessed, the user may join a channel (e.g. cs223)


	>> 	/join #cs223


Once a channel has been successfully joined, a user may do the following:
#### Client
- Join and leave channels
- Post a message to the channel
- Print the chat log for a specific channel
- List all users in a specified channel
- Terminate the client program

#### Operator
- Kick or ban users
- Promote or demote users to/from being opreators

All of the commands needed to do the above may be found in the server by running


	>>	 /help


---

## Additional Information

This server is currently unable to handle multiple clients at once. Hence, required features such as private messaging between clients in the same channel is not available.

The third and final phase of this project will tackle this issue. 




