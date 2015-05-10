/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hal.MPSCQueue.h"

hal::os::win32::SinglyLinkedList hal::MPSCQueue< void >::Node::m_node_pool;
bool                             hal::MPSCQueue< void >::Node::m_done = false;
