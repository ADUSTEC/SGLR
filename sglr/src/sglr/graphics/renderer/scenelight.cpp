#include "sglr/graphics/renderer/scenelight.h"
#include <sstream>

namespace sglr
{
	bool scenelight::m_init(shader* shader)
	{
		if (!shader)
			return false;

		m_shader = shader;
		return true;
	}

	void scenelight::newPointLight(const pointlightdata data) 
	{
		m_plIndex++;
		
		std::stringstream ss_pos;
		ss_pos << m_uplight << "[" << m_plIndex-1 << "].position";
		
		std::stringstream ss_diff;
		ss_diff << m_uplight << "[" << m_plIndex-1 << "].diffuse";

		// attenuation
		std::stringstream ss_aconst;
		ss_aconst << m_uplight << "[" << m_plIndex-1 << "].constant";
		std::stringstream ss_aquad;
		ss_aquad << m_uplight << "[" << m_plIndex-1 << "].quadratic";
		std::stringstream ss_alin;
		ss_alin << m_uplight << "[" << m_plIndex-1 << "].linear";
		//

		std::stringstream ss_intens;
		ss_intens << m_uplight << "[" << m_plIndex-1 << "].intensity";
		

		// set values
		pl_uposname = ss_pos.str();
		pl_udifname = ss_diff.str();
		pl_uconname = ss_aconst.str();
		pl_uquaname = ss_aquad.str();
		pl_ulinname = ss_alin.str();
		pl_uintname = ss_intens.str();
		
		m_pl[m_plIndex-1] = data;
		
	}

	void scenelight::newSpotLight(const spotlightdata data) 
	{
		m_spIndex++;

		std::stringstream ss_pos;
		ss_pos << m_usplight << "[" << m_spIndex - 1 << "].position";

		std::stringstream ss_ang;
		ss_ang << m_usplight << "[" << m_spIndex - 1 << "].angle";
		std::stringstream ss_inn;
		ss_inn << m_usplight << "[" << m_spIndex - 1 << "].innercone";
		std::stringstream ss_out;
		ss_out << m_usplight << "[" << m_spIndex - 1 << "].outercone";

		std::stringstream ss_diff;
		ss_diff << m_usplight << "[" << m_spIndex - 1 << "].diffuse";

		// attenuation
		std::stringstream ss_aconst;
		ss_aconst << m_usplight << "[" << m_spIndex - 1 << "].constant";
		std::stringstream ss_aquad;
		ss_aquad << m_usplight << "[" << m_spIndex - 1 << "].quadratic";
		std::stringstream ss_alin;
		ss_alin << m_usplight << "[" << m_spIndex - 1 << "].linear";
		//

		std::stringstream ss_intens;
		ss_intens << m_usplight << "[" << m_spIndex - 1 << "].intensity";


		// set values
		sp_uposname = ss_pos.str();
		sp_uangname = ss_ang.str();
		sp_uinnname = ss_inn.str();
		sp_uoutname = ss_out.str();
		sp_udifname = ss_diff.str();
		sp_uconname = ss_aconst.str();
		sp_uquaname = ss_aquad.str();
		sp_ulinname = ss_alin.str();
		sp_uintname = ss_intens.str();

		m_sp[m_spIndex - 1] = data;
	}
	
	void scenelight::createSunLight(const sunlightdata data) 
	{
		m_sIndex = 1;

		std::stringstream ss_ang;
		ss_ang << m_uslight << "[" << "0" << "].angle";

		std::stringstream ss_diff;
		ss_diff << m_uslight << "[" << "0" << "].diffuse";

		// set values
		s_uangname = ss_ang.str();
		s_udifname = ss_diff.str();

		m_s = data;
	}
		 
	void scenelight::revertAllPointLights() 
	{}
	void scenelight::revertAllSpotLights() 
	{}
	void scenelight::revertSunLight() 
	{}
		 
	void scenelight::updateScenePointLights() 
	{
		m_shader->setUniformInt("pointlightnum", m_plIndex);

		if (m_plIndex > 0)
		{
			for (int i = 0; i < m_plIndex; i++)
			{
				m_shader->setUniformVec3( pl_uposname.c_str(), m_pl[i].pl_position);
				m_shader->setUniformVec3( pl_udifname.c_str(), m_pl[i].pl_diffuse);
				m_shader->setUniformFloat(pl_uconname.c_str(), m_pl[i].pl_constant);
				m_shader->setUniformFloat(pl_uquaname.c_str(), m_pl[i].pl_quadratic);
				m_shader->setUniformFloat(pl_ulinname.c_str(), m_pl[i].pl_linear);
				m_shader->setUniformFloat(pl_uintname.c_str(), m_pl[i].pl_intensity);
			}
		}

		m_shader->setUniformVec3("u_globalambient", m_globalambient);
	}
	void scenelight::updateSceneSpotLights() 
	{
		m_shader->setUniformInt("spotlightnum", m_spIndex);

		if (m_spIndex > 0)
		{
			for (int i = 0; i < m_spIndex; i++)
			{
				m_shader->setUniformVec3( sp_uposname.c_str(), m_sp[i].sp_position);
				m_shader->setUniformVec3( sp_uangname.c_str(), m_sp[i].sp_angle);
				m_shader->setUniformFloat(sp_uinnname.c_str(), m_sp[i].sp_innercone);
				m_shader->setUniformFloat(sp_uoutname.c_str(), m_sp[i].sp_outercone);
				m_shader->setUniformVec3( sp_udifname.c_str(), m_sp[i].sp_diffuse);
				m_shader->setUniformFloat(sp_uconname.c_str(), m_sp[i].sp_constant);
				m_shader->setUniformFloat(sp_uquaname.c_str(), m_sp[i].sp_quadratic);
				m_shader->setUniformFloat(sp_ulinname.c_str(), m_sp[i].sp_linear);
				m_shader->setUniformFloat(sp_uintname.c_str(), m_sp[i].sp_intensity);
			}
		}

		m_shader->setUniformVec3("u_globalambient", m_globalambient);
	}
	void scenelight::updateSceneSunLight() 
	{
		m_shader->setUniformInt("sunlightnum", m_sIndex);

		if (m_sIndex > 0)
		{
			for (int i = 0; i < m_sIndex; i++)
			{
				m_shader->setUniformVec3( s_uangname.c_str(), m_s.s_angle);
				m_shader->setUniformVec3( s_udifname.c_str(), m_s.s_diffuse);
			}
		}

		m_shader->setUniformVec3("u_globalambient", m_globalambient);
	}
		 
}