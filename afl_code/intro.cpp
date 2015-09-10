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

#include "intro.h"

#include <string>
#include <iostream>
#include "Renderer.h"

/*
 * The following include is also generated automatically from the SDK build
 * tools. It contains integration code used by the AFL technology.
 */
#include "afl_introFactory.h"

#include <hana/execution.h>
#include <hana/exception.h>
#include <hana/logging.h>
#include <hana/table.h>
#include <hana/task.h>

#include <vector>
#include <ctime>

#if __cplusplus >= 201103L
#   include <memory>
namespace cpp11 = std
#elif defined (__GNUC__) && __GNUC__ >= 4 && defined (__GLIBCXX__)
#   include <tr1/memory>
namespace cpp11 = std::tr1;
#elif defined (_MSC_VER) && (_MSC_VER == 1500 && defined (_HAS_TR1) || _MSC_VER > 1500)
#   include <memory>
namespace cpp11 = stdext;
#else
#   error "unsupported platform/compiler"
#endif


AFLMETHODIMP CIntroAFL::RENDER_TILE(const int inputZ,
									const int inputX,
									const int inputY,
									hana::SharedTableViewer input,
                                    hana::SharedTable output) const
{
	using namespace hana;

    SharedColumn zColumn = output.columnByIndex(0);
    SharedColumn xColumn = output.columnByIndex(1);
    SharedColumn yColumn = output.columnByIndex(2);
    SharedColumn contentColumn = output.columnByIndex(3);

    SharedColumnViewer inputFromLngs = input.columnByIndex(0);
    SharedColumnViewer inputFromLats = input.columnByIndex(1);
    SharedColumnViewer inputToLngs = input.columnByIndex(2);
    SharedColumnViewer inputToLats = input.columnByIndex(3);
    SharedColumnViewer inputSpeedLevels = input.columnByIndex(4);
    SharedColumnViewer inputOneWays = input.columnByIndex(5);
    SharedColumnViewer inputOffsets = input.columnByIndex(6);
    SharedColumnViewer inputStrokeWidths = input.columnByIndex(7);

    std::vector<RoadSegment> segments;
    for (uint64_t i = 0, count = inputFromLngs.size(); i < count; ++i) {
		Double c_from_lng,c_from_lat,c_to_lng,c_to_lat,c_offset, c_stroke_width;
		int c_one_way,c_speed_level;
		inputFromLngs.toDouble(i, c_from_lng);
		inputFromLats.toDouble(i, c_from_lat);
		inputToLngs.toDouble(i, c_to_lng);
		inputToLats.toDouble(i, c_to_lat);
		inputSpeedLevels.toInt(i, c_speed_level);
		inputOneWays.toInt(i, c_one_way);
		inputOffsets.toDouble(i, c_offset);
		inputStrokeWidths.toDouble(i, c_stroke_width);

		Node from_node(c_from_lng, c_from_lat);
		Node to_node(c_to_lng, c_to_lat);

		RoadSegment seg(from_node, to_node, c_speed_level, c_one_way, c_offset, c_stroke_width);
		segments.push_back(seg);
    }

    Tile tile(inputZ, inputX, inputY);
	std::string str;
	getPngAsBase64(tile, segments, str);
	zColumn.fromInt(0, inputZ);
	xColumn.fromInt(0, inputX);
	yColumn.fromInt(0, inputY);
	contentColumn.fromString(0, str.c_str());
}
