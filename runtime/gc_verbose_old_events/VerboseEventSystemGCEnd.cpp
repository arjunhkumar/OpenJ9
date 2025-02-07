
/*******************************************************************************
 * Copyright IBM Corp. and others 1991
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

#include "VerboseEventSystemGCEnd.hpp"
#include "GCExtensions.hpp"
#include "VerboseEventStream.hpp"
#include "VerboseManagerOld.hpp"
#include "VerboseEventSystemGCStart.hpp"

/**
 * Create an new instance of a MM_VerboseEventSystemGCEnd event.
 * @param event Pointer to a structure containing the data passed over the hookInterface
 */
MM_VerboseEvent *
MM_VerboseEventSystemGCEnd::newInstance(MM_SystemGCEndEvent *event, J9HookInterface** hookInterface)
{
	MM_VerboseEventSystemGCEnd *eventObject;
	
	eventObject = (MM_VerboseEventSystemGCEnd *)MM_VerboseEvent::create(event->currentThread, sizeof(MM_VerboseEventSystemGCEnd));
	if(NULL != eventObject) {
		new(eventObject) MM_VerboseEventSystemGCEnd(event, hookInterface);
	}
	return eventObject;
}

/**
 * Populate events data fields.
 * The event calls the event stream requesting the address of events it is interested in.
 * When an address is returned it populates itself with the data.
 */
void
MM_VerboseEventSystemGCEnd::consumeEvents(void)
{
	MM_VerboseEventStream *eventStream = _manager->getEventStream();
	MM_VerboseEventSystemGCStart *event = NULL;
	
	/* Consume Events */
	if (NULL != (event = (MM_VerboseEventSystemGCStart *)eventStream->returnEvent(J9HOOK_MM_PRIVATE_SYSTEM_GC_START, _manager->getPrivateHookInterface(), (MM_VerboseEvent *)this))){
		_systemGCStartTime = event->getTimeStamp();
	} else {
		//Stream is corrupted, what now?
	}
	
	/* Set last Global collection time */
	_manager->setLastSystemGCTime(_time);
}

/**
 * Passes a format string and data to the output routine defined in the passed output agent.
 * @param agent Pointer to an output agent.
 */
void
MM_VerboseEventSystemGCEnd::formattedOutput(MM_VerboseOutputAgent *agent)
{
	UDATA indentLevel = _manager->getIndentLevel();
	U_64 timeInMicroSeconds;
		
	/* output the common GC start info */
	gcEndFormattedOutput(agent);
	
	if (!getTimeDeltaInMicroSeconds(&timeInMicroSeconds, _systemGCStartTime, _time + _exclusiveAccessTime)) {
		agent->formatAndOutput(static_cast<J9VMThread*>(_omrThread->_language_vmthread), indentLevel, "<warning details=\"clock error detected in time totalms\" />");
	}
	agent->formatAndOutput(static_cast<J9VMThread*>(_omrThread->_language_vmthread), indentLevel, "<time totalms=\"%llu.%03.3llu\" />",
		timeInMicroSeconds / 1000,
		timeInMicroSeconds % 1000
	);
	
	_manager->decrementIndent();
	indentLevel = _manager->getIndentLevel();
	
	agent->formatAndOutput(static_cast<J9VMThread*>(_omrThread->_language_vmthread), indentLevel, "</sys>");
	agent->endOfCycle(static_cast<J9VMThread*>(_omrThread->_language_vmthread));
}
