#pragma once
#include "mfem.hpp"

// MFEM mixed integrator to calculate the bilinear form,
// (u, (∇ . v))

//  For when your test function is a vector value represented by multiple copies of a scalar field i.e. H1^3,
//  and your trial function is a scalar in H1


namespace mfem {
    
class MixedWeakDivergenceIntegrator : public mfem::BilinearFormIntegrator
{
protected:
    mfem::Coefficient *a;
    
private:
    mfem::Vector trial_shape;
    mfem::Vector test_div_shape;
    mfem::DenseMatrix test_d_shape;
    mfem::DenseMatrix pelmat;
    mfem::DenseMatrix test_g_shape;
    mfem::DenseMatrix Jadj;

    const mfem::DofToQuad *trial_maps, *test_maps; ///< Not owned
    const mfem::GeometricFactors *geom;            ///< Not owned
    int dim;

public:

    MixedWeakDivergenceIntegrator(mfem::Coefficient &a) :
        a(&a), trial_maps(NULL), test_maps(NULL), geom(NULL) 
        {}        

    ~MixedWeakDivergenceIntegrator() {;}

    void AssembleElementMatrix2(const mfem::FiniteElement &trial_fe,
                                const mfem::FiniteElement &test_fe,
                                mfem::ElementTransformation &Trans,
                                mfem::DenseMatrix &elmat) override;

    const mfem::IntegrationRule& GetIntRule(const mfem::FiniteElement &trial_fe,
                                    const mfem::FiniteElement &test_fe,
                                    mfem::ElementTransformation &Trans);
};

}  // namespace mfem