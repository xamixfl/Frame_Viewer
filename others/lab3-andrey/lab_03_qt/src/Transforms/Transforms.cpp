//
// Created by nuelex on 09/05/25.
//

#include "Transforms.hpp"

Mover Mover::operator-()
{
    Mover mover{*this};
    
    mover.setDx(mover.getDx() * -1);
    mover.setDy(mover.getDy() * -1);
    mover.setDz(mover.getDz() * -1);

    return mover;
}


Mover Rotater::centerToMover() const
{
    const Mover mover{center};

    return mover;
}

Mover Scaler::centerToMover() const
{
    const Mover mover{center};

    return mover;
}
