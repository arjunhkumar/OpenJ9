/*******************************************************************************
 * Copyright IBM Corp. and others 2001
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
package jit.test.jitt.casting;

import org.testng.annotations.Test;
import org.testng.Assert;

@Test(groups = { "level.sanity","component.jit" })
public class I2SCast extends jit.test.jitt.Test {

	private short tstSimple(int x) {
		return (short)x;
	}

	private short tstComplex(int x) {
		return (short)justReturnIt(x);
	}
	
	private int justReturnIt(int x) {
		return x;
	}

	@Test
	public void testI2SCast() {
		for (int j = 0; j < sJitThreshold; j++) {
			tstSimple(0);
			tstComplex(0);
		}
		if (tstSimple(1) != (short)1) Assert.fail("Simple (short)1 incorrect");
		if (tstSimple(-1) != (short)-1) Assert.fail("Simple (short)-1 incorrect");
		if (tstSimple(0x12345678) != (short)0x12345678) Assert.fail("Simple (short)0x12345678 incorrect");
		if (tstComplex(1) != (short)1) Assert.fail("Complex (short)1 incorrect");
		if (tstComplex(-1) != (short)-1) Assert.fail("Complex (short)-1 incorrect");
		if (tstComplex(0x12345678) != (short)0x12345678) Assert.fail("Complex (short)0x12345678 incorrect");
	}

}
