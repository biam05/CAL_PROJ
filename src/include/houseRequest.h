#ifndef SRC_HOUSEREQUEST_H
#define SRC_HOUSEREQUEST_H

#include "spot.h"

class HouseRequest {
    enum type type;
    float quantity;

public:
    HouseRequest(enum type type, float quantity);

    enum type getType() const;

    void setType(enum type type);

    float getQuantity() const;

    void setQuantity(float quantity);
};


#endif //SRC_HOUSEREQUEST_H
