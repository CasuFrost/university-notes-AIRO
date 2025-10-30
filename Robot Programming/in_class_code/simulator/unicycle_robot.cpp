#include "unicycle_robot.h"
float radius_w;
float radius_px;

float velocity_translational = 0;
float velocity_rotational = 0;

UnicycleRobot::UnicycleRobot(WorldItem &parent_, const Isometry2f pip, float radius) : WorldItem(parent_, pip),
                                                                                       radius_w(radius)
{
    radius_px = _mapping.res() * radius_w;
}

void UnicycleRobot::timerTick(float dt)
{
    auto pose_backup = _pose_in_parent;
    float delta_x = velocity_translational * dt;
    float delta_theta = velocity_rotational * dt;
    Isometry2f delta(delta_x, 0, delta_theta);
    _pose_in_parent = _pose_in_parent * delta;
    if (isColliding())
    {
        _pose_in_parent = pose_backup;
    }
    WorldItem::timerTick(dt);
}
void UnicycleRobot::draw(cv::Mat canvas)
{
    auto piw = poseInWorld();
    Vector2i c_center = _mapping.world2grid(piw._translation);
    cv::circle(canvas, cv::Point(c_center.y(), c_center.x()), radius_px, cv::Scalar(1));

    Vector2f ep_w = piw * Vector2f(radius_w, 0);
    Vector2i ep_px = _mapping.world2grid(ep_w);

    cv::line(canvas,
             cv::Point(c_center.y(), c_center.x()),
             cv::Point(ep_px.y(), ep_px.x()),
             cv::Scalar(0), 1);
}

WorldItem *UnicycleRobot::isColliding()
{
    WorldItem *root = this;
    while (root->_parent)
    {
        root = root->_parent;
    }
    auto piw = poseInWorld();
    auto origin_px = _mapping.world2grid(piw._translation);
    auto robot_side = radius_px;
    int radius_px_square = radius_px * radius_px;

    const auto &grid = _mapping._grid;

    for (int r = -robot_side; r <= robot_side; ++r)
    {
        for (int c = -robot_side; c <= robot_side; ++c)
        {
            Vector2i p_local(r, c);
            if (p_local.dot(p_local) > radius_px_square)
                continue;
            Vector2i p = p_local + origin_px;
            if (!grid.inside(p))
                return root;
            auto v = grid.at(p.x(), p.y());

            if (v < 127)
                return root;
        }
    }
    return 0;
}
