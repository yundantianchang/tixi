/* 
* Copyright (C) 2007-2011 German Aerospace Center (DLR/SC)
*
* Created: 2010-08-13 Markus Litz <Markus.Litz@dlr.de>
* Changed: $Id$ 
*
* Version: $Revision$
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
   @file Utility functions used to perform xsl transformations.
*/

#include "xslTransformation.h"


char* xsltTransformToString(xmlDocPtr doc, char *xslFilename) {
    xmlDocPtr res;
    xmlChar *string;
	int len;
	xsltStylesheetPtr style;

    style = xsltParseStylesheetFile ((const xmlChar *) xslFilename);
    if (style == NULL) {
        fprintf(stderr, "xsltTransformToString: Could not parse XSLT file");
        return NULL;
    }

    res = xsltApplyStylesheet(style, doc, NULL);
    if(res == NULL) {
        fprintf(stderr, "xsltTransformToString: Problem applying stylesheet");
        return NULL;
    }

    xsltSaveResultToString(&string, &len, res, style);
    xmlFreeDoc(res);
    return (char *) string;
}


ReturnCode xsltTransformToFile(xmlDocPtr doc, char *xslFilename, char *outputFilename) {
    xmlDocPtr res;
    xsltStylesheetPtr style;

    if( (xslFilename == NULL) || (outputFilename == NULL) ) {
        fprintf(stderr, "xsltTransformToFile: Null pointer error");
        return FAILED;
    }

    style = xsltParseStylesheetFile ((const xmlChar *) xslFilename);
    if (style == NULL) {
        fprintf(stderr, "xsltTransformToFile: Could not parse XSLT file: %s", xslFilename);
        return FAILED;
    }

    res = xsltApplyStylesheet(style, doc, NULL);
    if(res == NULL){
        fprintf(stderr, "xsltTransformToFile: Problem applying stylesheet");
        return FAILED;
    }

    xsltSaveResultToFilename(outputFilename, res, style, 0);
    xmlFreeDoc(res);
    return SUCCESS;
}
