/********************************************************************
 * © 2015 SAP AG or an SAP affiliate company. All rights reserved.
 *
 * No part of this publication may be reproduced or transmitted in
 * any form or for any purpose without the express permission of
 * SAP AG. The information contained herein may be changed without
 * prior notice.
 * Some software products marketed by SAP AG and its distributors
 * contain proprietary software components of other software vendors.
 * National product specifications may vary.
 *
 * These materials are provided by SAP AG and its affiliated
 * companies ("SAP Group") for informational purposes only, without
 * representation or warranty of any kind, and SAP Group shall not be
 * liable for errors or omissions with respect to the materials. The
 * only warranties for SAP Group products and services are those that
 * are set forth in the express warranty statements accompanying such
 * products and services, if any. Nothing herein should be construed
 * as constituting an additional warranty.
 *
 * SAP and other SAP products and services mentioned herein as well
 * as their respective logos are trademarks or registered trademarks
 * of SAP AG in Germany and other countries.
 ********************************************************************/

#ifndef INTRO_AFL_H__
#define INTRO_AFL_H__

/*
 * The afl_intro.h is automatically generated when the SDK build tools run.
 */
#include "afl_intro.h"

/*
 * This is the AFL main class. As explained in afl_intro.afx it follows the
 * IxxxAFL and CxxxAFL naming convention. It must inherit from the  base
 * interface contained the afl_intro.h file.
 *
 * The AFs described in the afl_intro.afx are declared here and implemented
 * in the intro.cpp file.
 */
class CIntroAFL:
        public IIntroAFL
{
public:
    CIntroAFL () {}
    virtual ~CIntroAFL() {}

    /*
     * This macros allows the back-end to get a handle to this AFL and
     * eventually invoke the AFs.
     */
    AFL_QUERYINTERFACE(IntroAFL)


    AFLMETHOD(RENDER_TILE)(const int inputZ,
    									const int inputX,
    									const int inputY,
    									hana::SharedTableViewer input,
                                        hana::SharedTable output) const;

};

#endif // INTRO_AFL_H__
