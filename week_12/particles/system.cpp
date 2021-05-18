#include "system.hpp"

void System::initialize()
{
	const auto size = std::size(m_particles);

	for (auto i = 0U; i < size-4; ++i)
	{
		m_links.push_back(Link(particle(i), particle((i+1) % size), 0.5f));
	}
    m_links.push_back(Link(particle(size-4), particle(size-3), 0.5f));
    m_links.push_back(Link(particle(size-3), particle(0), 0.5f));
    for (auto i = 0U; i < size-1; ++i) {
        if (i != size-2) {
            m_links.push_back(Link(particle(i), particle(size - 2), 0.005f));
        }
        m_links.push_back(Link(particle(i), particle(size-1), 0.005f));
    }
}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void System::update() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(0.25f);

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
		}
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}

	m_pressure.update();
}