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

#include "j9protos.h"
#include "j9consts.h"
#include "util_internal.h"


J9Class *
allSubclassesStartDo(J9Class * rootClass, J9SubclassWalkState * subclassState, UDATA includeRootClass)
{
	subclassState->rootDepth = J9CLASS_DEPTH(rootClass);
	subclassState->currentClass = rootClass;

	if (includeRootClass) {
		return rootClass;
	}

	return allSubclassesNextDo(subclassState);
}



J9Class *
allSubclassesNextDo(J9SubclassWalkState * subclassState)
{
	J9Class * nextSubclass = subclassState->currentClass->subclassTraversalLink;

	if (nextSubclass != NULL) {
		if (J9CLASS_DEPTH(nextSubclass) <= subclassState->rootDepth) {
			nextSubclass = NULL;
		} else {
			subclassState->currentClass = nextSubclass;
		}
	}

	return nextSubclass;
}




