/*[INCLUDE-IF Sidecar18-SE]*/
/*******************************************************************************
 * Copyright IBM Corp. and others 2012
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
package com.ibm.java.diagnostics.utils.plugins;

import java.util.HashMap;
import java.util.Map;

/**
 * The annotations that are found on a class.
 * 
 * @author adam
 *
 */
public class Annotation {
	private final String classname;
	private final Map<String, Object> values = new HashMap<String, Object>();
	
	public Annotation(String classname) {
		this.classname = classname;
	}
	
	public Map<String, Object> getValues() {
		return values;
	}

	/**
	 * Get the value of an annotation when it only contains 
	 * a single value.
	 * 
	 * @return the value or the first one in the list of a multi-value (the order is not guaranteed in this case)
	 */
	public Object getValue() {
		if(values.isEmpty()) {
			return null;
		}
		return values.values().iterator().next();
	}
	
	public String getClassname() {
		return classname;
	}
	
	public void addEntry(String name, Object value) {
		values.put(name, value);
	}

	@Override
	public boolean equals(Object o) {
		if((o == null) || !(o instanceof Annotation)) {
			return false;
		}
		Annotation compareTo = (Annotation) o;
		return classname.equals(compareTo.classname);
	}

	@Override
	public int hashCode() {
		return classname.hashCode();
	}
	
	
}
