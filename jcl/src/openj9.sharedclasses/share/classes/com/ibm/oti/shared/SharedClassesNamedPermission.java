/*[INCLUDE-IF SharedClasses & (JAVA_SPEC_VERSION < 24)]*/
package com.ibm.oti.shared;

/*
 * Copyright IBM Corp. and others 2018
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
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0-only WITH Classpath-exception-2.0 OR GPL-2.0-only WITH OpenJDK-assembly-exception-1.0
 */

import java.security.BasicPermission;

/**
 * This class defines shared cache permissions as described in the following table.
 *
 * <table border=1 style="padding=5px">
 * <caption>Shared Cache Permissions</caption>
 * <tr>
 * <th style="text-align:left">Permission Name</th>
 * <th style="text-align:left">Allowed Action</th>
 * </tr>
 * <tr>
 * <td>getSharedCacheInfo</td>
 * <td>Obtaining available shared cache information.
 *     See {@link SharedClassUtilities#getSharedCacheInfo(String, int, boolean)}.</td>
 * </tr>
 * <tr>
 * <td>destroySharedCache</td>
 * <td>Destroying a shared cache.
 *     See {@link SharedClassUtilities#destroySharedCache(String, int, String, boolean)}.</td>
 * </tr>
 * </table>
 */
public final class SharedClassesNamedPermission extends BasicPermission {

	private static final long serialVersionUID = -4800623387760880313L;

	/*
	 * Helper class to avoid creating permission objects unless needed at runtime.
	 */
	static final class SharedPermissions {
		public static final SharedClassesNamedPermission getSharedCacheInfo = new SharedClassesNamedPermission("getSharedCacheInfo"); //$NON-NLS-1$
		public static final SharedClassesNamedPermission destroySharedCache = new SharedClassesNamedPermission("destroySharedCache"); //$NON-NLS-1$
	}

	/**
	 * Create a representation of the named permissions.
	 *
	 * @param name
	 *          name of the permission
	 */
	public SharedClassesNamedPermission(String name) {
		super(name);
	}

	/**
	 * Create a representation of the named permissions.
	 *
	 * @param name
	 *          name of the permission
	 * @param actions
	 *          not used, must be null or an empty string
	 * @throws IllegalArgumentException
	 *          if actions is not null or an empty string
	 */
	public SharedClassesNamedPermission(String name, String actions) {
		super(name, actions);

		// ensure that actions is null or an empty string
		if (!((null == actions) || actions.isEmpty())) {
			throw new IllegalArgumentException();
		}
	}

}
