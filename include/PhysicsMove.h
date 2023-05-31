#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

// Disable MSVC analysis warnings for the box2d include
#pragma warning(push)
#pragma warning(disable: 26495 26813)
#include "box2d/box2d.h"
#pragma warning(pop)

#include "Resources.h"


class PhysicsMove {
public:
	PhysicsMove()
        : m_gravity(0.0f, -10.0f), m_world(std::make_unique<b2World>(m_gravity)), m_groundBody(m_world->CreateBody(&m_groundBodyDef)), m_body(m_world->CreateBody(&m_bodyDef)), m_timeStep(1.0f / 60.0f), m_velocityIterations(6), m_positionIterations(2),m_position(m_body->GetPosition()), m_angle(m_body->GetAngle()), m_rect({ 40.f, 40.f }) //, m_worldStepCounter(60)
    {
        m_groundBodyDef.position.Set(0.0f, -10.0f);
        m_groundBox.SetAsBox(50.0f, 10.0f);
        m_groundBody->CreateFixture(&m_groundBox, 0.0f);

        m_bodyDef.type = b2_dynamicBody;
        m_bodyDef.position.Set(0.0f, 4.0f);

        m_dynamicBox.SetAsBox(1.0f, 1.0f);

        m_fixtureDef.shape = &m_dynamicBox;
        m_fixtureDef.density = 1.0f;
        m_fixtureDef.friction = 0.3f;
        m_body->CreateFixture(&m_fixtureDef);

        m_rect.setFillColor(sf::Color::Green);
    }
	
    ~PhysicsMove() = default;

    void setMove()
    {
        // First, cause the world to be updated to the next step
        m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
        
        // Then, get the new position and angle from box2d object ...
        m_position = m_body->GetPosition();
        
        // (box2d numbers are not in pixels, so we need some scaling here)
        m_position *= 100.f;
        m_angle = m_body->GetAngle();
    }

    b2Vec2 getMove()
    {
        return m_position;
    }

    float getAngle()
    {
        return m_angle;
    }


private:
    sf::RenderWindow& m_window = Resources::getInstance().getWindow();

    b2Vec2 m_gravity;
    std::unique_ptr<b2World> m_world;
    b2BodyDef m_groundBodyDef;
    b2Body* m_groundBody;
    b2PolygonShape m_groundBox;
    b2BodyDef m_bodyDef;
    
    b2Body* m_body;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;
    
    float m_timeStep;
    int32 m_velocityIterations;
    int32 m_positionIterations;

    b2Vec2 m_position;
    float m_angle;
    
    sf::RectangleShape m_rect;

    // unsigned int m_worldStepCounter;
};