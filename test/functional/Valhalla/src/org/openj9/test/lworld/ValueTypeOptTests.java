/*******************************************************************************
 * Copyright IBM Corp. and others 2022
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
package org.openj9.test.lworld;

import org.testng.Assert;
import static org.testng.Assert.*;
import org.testng.annotations.Test;
import org.testng.annotations.BeforeClass;


@Test(groups = { "level.sanity" })
public class ValueTypeOptTests {
	public primitive static class Pair {
		public final int x, y;

		public Pair(int x, int y) {
			this.x = x; this.y = y;
		}
	}

	public static class EscapeException extends RuntimeException {
		public Object escapingObject;

		public EscapeException(Object o) {
			escapingObject = o;
		}
	}

	public static int result = 0;
	public static Pair[] arr = new Pair[] { new Pair(3, 4) };

	@Test(priority=1)
	static public void testEAOpportunity1() throws Throwable {
		result = 0;

		evalTestEA1();
		evalTestEA1();

		assertEquals(result, 1000);
	}

	static private void evalTestEA1() {
		// Test situation where EA could apply to value p1, but must
		// allocate contiguously
		for (int i = 0; i < 100; i++) {
			Pair p1 = new Pair(1, 2);
			Pair p2 = arr[0];

			Pair p3;
			Pair p4;

			if (i % 2 == 0) {
				p3 = p2;
				p4 = p1;
			} else {
				p3 = p1;
				p4 = p2;
			}
			result += p3.x + p4.y;
		}
	}

	@Test(priority=1)
	static public void testEAOpportunity2() throws Throwable {
		result = 0;

		evalTestEA2();
		evalTestEA2();

		assertEquals(result, 400);
	}

	public static Pair testEA2Field;

	static private void evalTestEA2() {
		int x = 1; int y = 2;

		for (int i = 0; i < 100; i++) {
			Pair p1 = new Pair(x, y);
			int updatex = (x-y)*(x-y);
			int updatey = y*(y-x);
			x = updatex;
			y = updatey;
			if (p1.x*p1.y != 2) testEA2Field = p1;  // Looks like value might escape (but never actually does)

			result += x*y;
		}
	}

	static private void evalTestEA3() {
		for (int i = 0; i < 100; i++) {
			Pair[] arr = new Pair[] {new Pair(1, 2), new Pair(3, 4)};
			for (int j = 0; j < arr.length; j++) {
				Pair val = arr[j%arr.length];
				result += val.x + val.y;
			}
		}
	}

	@Test(priority=1)
	static public void testEAOpportunity3() throws Throwable {
		result = 0;

		evalTestEA3();
		evalTestEA3();

		assertEquals(result, 2000);
	}

	@Test(priority=1)
	static public void testEAOpportunity4() throws Throwable {
	}
}
