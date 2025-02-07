/*[INCLUDE-IF Sidecar18-SE]*/
/*******************************************************************************
 * Copyright IBM Corp. and others 2006
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
package com.ibm.dtfj.corereaders.zos.le;

import javax.imageio.stream.ImageInputStream;
import java.io.IOException;

/* This class was generated automatically by com.ibm.dtfj.corereaders.zos.util.Xml2Java */

public final class Ceexedb32Template implements CeexedbTemplate {

    public int length() {
        return 1216;
    }

    public long getCeeedbenvar(ImageInputStream inputStream, long address) throws IOException {
        inputStream.seek(address + 88);
        return inputStream.readUnsignedInt() & 0xffffffffL;
    }
    public int getCeeedbenvar$offset() {
        return 88;
    }
    public int getCeeedbenvar$length() {
        return 32;
    }
    public long getCeeedb_ceeosigr(ImageInputStream inputStream, long address) throws IOException {
        inputStream.seek(address + 96);
        return inputStream.readUnsignedInt() & 0xffffffffL;
    }
    public int getCeeedb_ceeosigr$offset() {
        return 96;
    }
    public int getCeeedb_ceeosigr$length() {
        return 32;
    }
    public long getCeeedbdba(ImageInputStream inputStream, long address) throws IOException {
        inputStream.seek(address + 924);
        return inputStream.readUnsignedInt() & 0xffffffffL;
    }
    public int getCeeedbdba$offset() {
        return 924;
    }
    public int getCeeedbdba$length() {
        return 32;
    }
    public long getCeeedb_dlcb_first(ImageInputStream inputStream, long address) throws IOException {
        inputStream.seek(address + 1096);
        return inputStream.readUnsignedInt() & 0xffffffffL;
    }
    public int getCeeedb_dlcb_first$offset() {
        return 1096;
    }
    public int getCeeedb_dlcb_first$length() {
        return 32;
    }
}
