#ifndef SUBRENDERER_H_INCLUDED
#define SUBRENDERER_H_INCLUDED

#include "../pogel/pogel.h"

namespace Renderer
{
    class SubRenderer;
}

#include "light.h"
#include "camera.h"
#include "physics.h"

#include "draw.h"

#include "renderer.h"

namespace Renderer
{
    class SubRenderer : public POGEL::VIEW
    {
        private:
            ClassList<Renderer::Physics::Simulation*> simulationBindings;
        protected:
            POGEL::VECTOR globalTempRefpos;
            POGEL::POINT globalTempCampos;
            POGEL::POINT globalTempInvCampos;

        public:
            template<class T> inline ClassList< DataWraper<POGEL::PHYSICS::SOLID*,float> > __sortedDraw(T*);

            Renderer::Camera::Viewpoint camera;
            Renderer::Lighting::Light lights[MAXNUMLIGHTS];

            SubRenderer();
            SubRenderer( const std::string& );
            SubRenderer( const std::string& ,float);
            ~SubRenderer();

            void setLight( const Renderer::Lighting::Light&, int );

            Renderer::Physics::Simulation* getBoundSimulation( const std::string& );

            int addSimulationBinding( const std::string& );
            int removeSimulationBinding( const std::string& );
            int removeAllSimulationBindings();

            void scenesetup();
            void scene();

            void draw();
    };

    Renderer::SubRenderer* requestSubRenderer( const std::string& );
    void RenderAllSubRenderers();
}

#endif // SUBRENDERER_H_INCLUDED
