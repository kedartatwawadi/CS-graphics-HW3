/*
 * coordinates_3D_t.h
 *
 *  Created on: Sep 23, 2012
 *      Author: ayesha, kedar
 */

#ifndef COORDINATES_3D_T_H_
#define COORDINATES_3D_T_H_

#include "vector_t.h"

class coordinates_3D_t {
public:
	coordinates_3D_t();
    coordinates_3D_t(vector_t vector);

    vector_t getCcs();
    void setCcs(vector_t ccs);

    vector_t getDcs();
    void setDcs(vector_t dcs);

    vector_t getNdcs();
    void setNdcs(vector_t ndcs);

    vector_t getVcs();
    void setVcs(vector_t vcs);

    vector_t getWcs();
    void setWcs(vector_t wcs);

	vector_t getCcsClipped();
	void setCcsClipped(vector_t ccs_clipped);

	vector_t getDcsClipped();
	void setDcsClipped(vector_t dcs_clipped);

	vector_t getNdcsClipped();
	void setNdcsClipped(vector_t ndcs_clipped);

	double getWCcs();
	void setWCcs(double w_ccs);

private:
    vector_t Wcs;
    vector_t Vcs;
    vector_t Ccs;
    vector_t Ndcs;
    vector_t Dcs;
    vector_t CcsClipped;
    vector_t NdcsClipped;
    vector_t DcsClipped;
    double wCcs;
};

#endif /* COORDINATES_3D_T_H_ */
