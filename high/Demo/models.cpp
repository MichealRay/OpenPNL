#include "pnlHigh.hpp"
#include <conio.h>
#include "console.h"

PNLW_BEGIN

BayesNet *AsiaModel()
{ 
    BayesNet *net;
    net = new BayesNet();

    // nodes
    textcolor(WHITE);
    net->AddNode(discrete^"Smoking", "True False"); 
    printf("\n net->AddNode(discrete^\"Smoking\", \"True False\");");
    textcolor(LIGHTGREEN);

    printf("\t\t\t\tAdding of nodes is in process....");
    _sleep(2000);
    textcolor(WHITE);

    net->AddNode(discrete^"VisitToAsia", "True False");
    printf("\n net->AddNode(discrete^\"VisitToAsia\", \"True False\");");
    _sleep(1000);

    net->AddNode(discrete^"Bronchitis", "True False"); 
    printf("\n net->AddNode(discrete^\"Bronchitis\", \"True False\");");
    _sleep(1000);

    net->AddNode(discrete^"LungCancer", "True False"); 
    printf("\n net->AddNode(discrete^\"LungCancer\", \"True False\");");
    _sleep(1000);
    
    net->AddNode(discrete^"Tuberculosis", "True False"); 
    printf("\n net->AddNode(discrete^\"Tuberculosis\", \"True False\");");
    _sleep(1000);

    net->AddNode(discrete^"Dyspnoea", "True False"); 
    printf("\n net->AddNode(discrete^\"Dyspnoea\", \"True False\");");
    _sleep(1000);

    net->AddNode(discrete^"CancerOrTuberculosis", "True False");
    printf("\n net->AddNode(discrete^\"CancerOrTuberculosis\", \"True False\");");
    _sleep(1000);
    
    net->AddNode(discrete^"XRayPositive", "True False");
    printf("\n net->AddNode(discrete^\"XRayPositive\", \"True False\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All nodes are added....\n");
    getch();

    // arcs
    textcolor(WHITE);
    net->AddArc("Smoking", "Bronchitis LungCancer");
    printf("\n net->AddArc(\"Smoking\", \"Bronchitis LungCancer\");");

    textcolor(LIGHTGREEN);
    printf("\t\t\t\tAdding of arcs is in process....");
    _sleep(2000);

    textcolor(WHITE);
    net->AddArc("VisitToAsia", "Tuberculosis");
    printf("\n net->AddArc(\"VisitToAsia\", \"Tuberculosis\");");
    _sleep(1000);

    net->AddArc("LungCancer Tuberculosis", "CancerOrTuberculosis");
    printf("\n net->AddArc(\"LungCancer Tuberculosis\", \"CancerOrTuberculosis\");");
    _sleep(1000);

    net->AddArc("Bronchitis", "Dyspnoea");
    printf("\n net->AddArc(\"Bronchitis\", \"Dyspnoea\");");
    _sleep(1000);

    net->AddArc("CancerOrTuberculosis", "Dyspnoea XRayPositive");
    printf("\n net->AddArc(\"CancerOrTuberculosis\", \"Dyspnoea XRayPositive\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All arcs are added....\n");
    getch();
    // distributions
    textcolor(WHITE);
    net->SetPTabular("Smoking^True Smoking^False", "0.5 0.5");
    printf("\n net->SetPTabular(\"Smoking^True Smoking^False\", \"0.5 0.5\");");
    
    textcolor(LIGHTGREEN);
    printf("\t\t\tAdding of distributions is in process....");
    _sleep(2000);

    textcolor(WHITE);
    net->SetPTabular("VisitToAsia^True VisitToAsia^False", "0.01 0.99");
    printf("\n net->SetPTabular(\"VisitToAsia^True VisitToAsia^False\", \"0.01 0.99\");");
    _sleep(1000);

    net->SetPTabular("Bronchitis^True", "0.3", "Smoking^False");
    printf("\n net->SetPTabular(\"Bronchitis^True\", \"0.3\", \"Smoking^False\");");
    _sleep(1000);

    net->SetPTabular("Bronchitis^False", "0.7", "Smoking^False");
    printf("\n net->SetPTabular(\"Bronchitis^False\", \"0.7\", \"Smoking^False\");");
    _sleep(1000);

    net->SetPTabular("Bronchitis^True", "0.4", "Smoking^True");
    printf("\n net->SetPTabular(\"Bronchitis^True\", \"0.4\", \"Smoking^True\");");
    _sleep(1000);

    net->SetPTabular("Bronchitis^False", "0.6", "Smoking^True");
    printf("\n net->SetPTabular(\"Bronchitis^False\", \"0.6\", \"Smoking^True\");");
    _sleep(1000);

    net->SetPTabular("LungCancer^True", "0.01","Smoking^False");
    printf("\n net->SetPTabular(\"LungCancer^True\", \"0.01\",\"Smoking^False\");");
    _sleep(1000);

    net->SetPTabular("LungCancer^False", "0.99","Smoking^False");
    printf("\n net->SetPTabular(\"LungCancer^False\", \"0.99\",\"Smoking^False\");");
    _sleep(1000);

    net->SetPTabular("LungCancer^True", "0.1","Smoking^True");
    printf("\n net->SetPTabular(\"LungCancer^True\", \"0.1\",\"Smoking^True\");");
    _sleep(1000);

    net->SetPTabular("LungCancer^False", "0.9","Smoking^True");
    printf("\n net->SetPTabular(\"LungCancer^False\", \"0.9\",\"Smoking^True\");");
    _sleep(1000);

    net->SetPTabular("Tuberculosis^True", "0.01", "VisitToAsia^False");
    printf("\n net->SetPTabular(\"Tuberculosis^True\", \"0.01\", \"VisitToAsia^False\");");
    _sleep(1000);

    net->SetPTabular("Tuberculosis^False", "0.99", "VisitToAsia^False");
    printf("\n net->SetPTabular(\"Tuberculosis^False\", \"0.99\", \"VisitToAsia^False\");");
    _sleep(1000);

    net->SetPTabular("Tuberculosis^True", "0.05", "VisitToAsia^True" );
    printf("\n net->SetPTabular(\"Tuberculosis^True\", \"0.05\", \"VisitToAsia^True\" );");
    _sleep(1000);
  
    net->SetPTabular("Tuberculosis^False", "0.95", "VisitToAsia^True" );
    printf("\n net->SetPTabular(\"Tuberculosis^False\", \"0.95\", \"VisitToAsia^True\" );");
    _sleep(1000);

    net->SetPTabular("CancerOrTuberculosis^True", "0.0", "LungCancer^False Tuberculosis^False");
    printf("\n net->SetPTabular(\"CancerOrTuberculosis^True\", \"0.0\", \n \t \"LungCancer^False Tuberculosis^False\");");
    _sleep(1000);
    
    net->SetPTabular("CancerOrTuberculosis^False", "1.0", "LungCancer^False Tuberculosis^False");
    printf("\n net->SetPTabular(\"CancerOrTuberculosis^False\", \"1.0\", \n \t \"LungCancer^False Tuberculosis^False\");");
    _sleep(1000);

    net->SetPTabular("CancerOrTuberculosis^True CancerOrTuberculosis^False", "1.0 0.0", "LungCancer^False Tuberculosis^True");
    printf("\n net->SetPTabular(\"CancerOrTuberculosis^True CancerOrTuberculosis^False\",\n \t \"1.0 0.0\", \"LungCancer^False Tuberculosis^True\");");
    _sleep(1000);
    
    net->SetPTabular("CancerOrTuberculosis^True CancerOrTuberculosis^False", "1.0 0.0", "LungCancer^True Tuberculosis^False");
    printf("\n net->SetPTabular(\"CancerOrTuberculosis^True CancerOrTuberculosis^False\", \n \t\"1.0 0.0\", \"LungCancer^True Tuberculosis^False\");");
    _sleep(1000);
    
    net->SetPTabular("CancerOrTuberculosis^True CancerOrTuberculosis^False", "1.0 0.0", "LungCancer^True Tuberculosis^True");
    printf("\n net->SetPTabular(\"CancerOrTuberculosis^True CancerOrTuberculosis^False\", \n \t\"1.0 0.0\", \"LungCancer^True Tuberculosis^True\");");
    _sleep(1000);

    net->SetPTabular("Dyspnoea^True Dyspnoea^False", "0.1 0.9", "Bronchitis^False CancerOrTuberculosis^False");
    printf("\n net->SetPTabular(\"Dyspnoea^True Dyspnoea^False\", \"0.1 0.9\", \n \t\"Bronchitis^False CancerOrTuberculosis^False\");");
    _sleep(1000);
    
    net->SetPTabular("Dyspnoea^True Dyspnoea^False", "0.7 0.3", "Bronchitis^False CancerOrTuberculosis^True");
    printf("\n net->SetPTabular(\"Dyspnoea^True Dyspnoea^False\", \"0.7 0.3\", \n \t\"Bronchitis^False CancerOrTuberculosis^True\");");
    _sleep(1000);
    
    net->SetPTabular("Dyspnoea^True Dyspnoea^False", "0.8 0.2", "Bronchitis^True CancerOrTuberculosis^False");
    printf("\n net->SetPTabular(\"Dyspnoea^True Dyspnoea^False\", \"0.8 0.2\", \n \t\"Bronchitis^True CancerOrTuberculosis^False\");");
    _sleep(1000);
    
    net->SetPTabular("Dyspnoea^True Dyspnoea^False", "0.9 0.1", "Bronchitis^True CancerOrTuberculosis^True");
    printf("\n net->SetPTabular(\"Dyspnoea^True Dyspnoea^False\", \"0.9 0.1\", \n \t\"Bronchitis^True CancerOrTuberculosis^True\");");
    _sleep(1000);

    net->SetPTabular("XRayPositive^True XRayPositive^False", "0.05 0.95", "CancerOrTuberculosis^False");	
    printf("\n net->SetPTabular(\"XRayPositive^True XRayPositive^False\", \"0.05 0.95\", \n \t\"CancerOrTuberculosis^False\");");
    _sleep(1000);
    
    net->SetPTabular("XRayPositive^True XRayPositive^False", "0.98 0.02", "CancerOrTuberculosis^True");
    printf("\n net->SetPTabular(\"XRayPositive^True XRayPositive^False\", \"0.98 0.02\", \n \t\"CancerOrTuberculosis^True\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All distributions are added....\n");
    textcolor(WHITE);
    getch();
    return net;
}

LIMID *PigsModel()
{
    LIMID *net;
    net = new LIMID();

    textcolor(WHITE);
    net->AddNode(chance^"h1", "False True");
    printf("\n net->AddNode(chance^\"h1\", \"False True\");");
    
    textcolor(LIGHTGREEN);
    printf("\t\t\t\t\t\tAdding of nodes is in process....");
    _sleep(2000);
    textcolor(WHITE);

    net->AddNode(chance^"t1", "False True");
    printf("\n net->AddNode(chance^\"t1\", \"False True\");");
    _sleep(1000);
    
    net->AddNode(decision^"d1", "False True");
    printf("\n net->AddNode(decision^\"d1\", \"False True\");");
    _sleep(1000);

    net->AddNode(chance^"h2", "False True");
    printf("\n net->AddNode(chance^\"h2\", \"False True\");");
    _sleep(1000);
    
    net->AddNode(chance^"t2", "False True");
    printf("\n net->AddNode(chance^\"t2\", \"False True\");");
    _sleep(1000);
    
    net->AddNode(decision^"d2", "False True");
    printf("\n net->AddNode(decision^\"d2\", \"False True\");");
    _sleep(1000);

    net->AddNode(chance^"h3", "False True");
    printf("\n net->AddNode(chance^\"h3\", \"False True\");");
    _sleep(1000);
    
    net->AddNode(chance^"t3", "False True");
    printf("\n net->AddNode(chance^\"t3\", \"False True\");");
    _sleep(1000);
    
    net->AddNode(decision^"d3", "False True");
    printf("\n net->AddNode(decision^\"d3\", \"False True\");");
    _sleep(1000);

    net->AddNode(chance^"h4", "False True");
    printf("\n net->AddNode(chance^\"h4\", \"False True\");");
    _sleep(1000);

    net->AddNode(value^"u1", "Cost");
    printf("\n net->AddNode(value^\"u1\", \"Cost\");");
    _sleep(1000);
    
    net->AddNode(value^"u2", "Cost");
    printf("\n net->AddNode(value^\"u2\", \"Cost\");");
    _sleep(1000);
    
    net->AddNode(value^"u3", "Cost");
    printf("\n net->AddNode(value^\"u3\", \"Cost\");");
    _sleep(1000);
    
    net->AddNode(value^"u4", "Cost");
    printf("\n net->AddNode(value^\"u4\", \"Cost\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All nodes are added....\n");
    getch();

    // arcs
    textcolor(WHITE);
    net->AddArc("h1", "h2 t1");
    printf("\n net->AddArc(\"h1\", \"h2 t1\");");

    textcolor(LIGHTGREEN);
    printf("\t\t\t\t\t\t\t\tAdding of arcs is in process....");
    _sleep(2000);

    textcolor(WHITE);    
    net->AddArc("h2", "h3 t2");
    printf("\n net->AddArc(\"h2\", \"h3 t2\");");
    _sleep(1000);
    
    net->AddArc("t1", "d1");
    printf("\n net->AddArc(\"t1\", \"d1\");");
    _sleep(1000);
    
    net->AddArc("t2", "d2");
    printf("\n net->AddArc(\"t2\", \"d2\");");
    _sleep(1000);
    
    net->AddArc("d1", "h2 u1");
    printf("\n net->AddArc(\"d1\", \"h2 u1\");");
    _sleep(1000);
    
    net->AddArc("h3", "h4 t3");
    printf("\n net->AddArc(\"h3\", \"h4 t3\");");
    _sleep(1000);
    
    net->AddArc("t3", "d3");
    printf("\n net->AddArc(\"t3\", \"d3\");");
    _sleep(1000);
    
    net->AddArc("d2", "h3 u2");
    printf("\n net->AddArc(\"d2\", \"h3 u2\");");
    _sleep(1000);
    
    net->AddArc("d3", "h4 u3");
    printf("\n net->AddArc(\"d3\", \"h4 u3\");");
    _sleep(1000);
    
    net->AddArc("h4", "u4");
    printf("\n net->AddArc(\"h4\", \"u4\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All arcs are added....\n");
    getch();

    // distributions
    textcolor(WHITE);

    net->SetPChance("h1^False h1^True", "0.9 0.1");
    printf("\n net->SetPChance(\"h1^False h1^True\", \"0.9 0.1\");");

    textcolor(LIGHTGREEN);
    printf("\t\t\t\t\tAdding of distributions is in process....");
    _sleep(2000);
    textcolor(WHITE);

    net->SetPChance("t1^False t1^True", "0.1 0.9", "h1^False");
    printf("\n net->SetPChance(\"t1^False t1^True\", \"0.1 0.9\", \"h1^False\");");
    _sleep(1000);
    
    net->SetPChance("t1^False t1^True", "0.8 0.2", "h1^True");
    printf("\n net->SetPChance(\"t1^False t1^True\", \"0.8 0.2\", \"h1^True\");");
    _sleep(1000);
    
    net->SetPDecision("d1^False d1^True", "0.5 0.5", "t1^False");
    printf("\n net->SetPDecision(\"d1^False d1^True\", \"0.5 0.5\", \"t1^False\");");
    _sleep(1000);
    
    net->SetPDecision("d1^False d1^True", "0.5 0.5", "t1^True");
    printf("\n net->SetPDecision(\"d1^False d1^True\", \"0.5 0.5\", \"t1^True\");");
    _sleep(1000);

    net->SetValueCost("u1^Cost", "-100.0", "d1^False");
    printf("\n net->SetValueCost(\"u1^Cost\", \"-100.0\", \"d1^False\");");
    _sleep(1000);
    
    net->SetValueCost("u1^Cost", "0.0", "d1^True");
    printf("\n net->SetValueCost(\"u1^Cost\", \"0.0\", \"d1^True\");");
    _sleep(1000);
    
    net->SetPChance("h2^False h2^True", "0.9 0.1", "h1^False d1^False");
    printf("\n net->SetPChance(\"h2^False h2^True\", \"0.9 0.1\", \"h1^False d1^False\");");
    _sleep(1000);
    
    net->SetPChance("h2^False h2^True", "0.8 0.2", "h1^False d1^True");
    printf("\n net->SetPChance(\"h2^False h2^True\", \"0.8 0.2\", \"h1^False d1^True\");");
    _sleep(1000);
    
    net->SetPChance("h2^False h2^True", "0.5 0.5", "h1^True d1^False");
    printf("\n net->SetPChance(\"h2^False h2^True\", \"0.5 0.5\", \"h1^True d1^False\");");
    _sleep(1000);
    
    net->SetPChance("h2^False h2^True", "0.1 0.9", "h1^True d1^True");
    printf("\n net->SetPChance(\"h2^False h2^True\", \"0.1 0.9\", \"h1^True d1^True\");");
    _sleep(1000);
    
    net->SetPChance("t2^False t2^True", "0.1 0.9", "h2^False");
    printf("\n net->SetPChance(\"t2^False t2^True\", \"0.1 0.9\", \"h2^False\");");
    _sleep(1000);
    
    net->SetPChance("t2^False t2^True", "0.8 0.2", "h2^True");
    printf("\n net->SetPChance(\"t2^False t2^True\", \"0.8 0.2\", \"h2^True\");");
    _sleep(1000);
    
    net->SetPDecision("d2^False d2^True", "0.5 0.5", "t2^False");
    printf("\n net->SetPDecision(\"d2^False d2^True\", \"0.5 0.5\", \"t2^False\");");
    _sleep(1000);
    
    net->SetPDecision("d2^False d2^True", "0.5 0.5", "t2^True");
    printf("\n net->SetPDecision(\"d2^False d2^True\", \"0.5 0.5\", \"t2^True\");");
    _sleep(1000);
    
    net->SetValueCost("u2^Cost", "-100.0", "d2^False");
    printf("\n net->SetValueCost(\"u2^Cost\", \"-100.0\", \"d2^False\");");
    _sleep(1000);
    
    net->SetValueCost("u2^Cost", "0.0", "d2^True");
    printf("\n net->SetValueCost(\"u2^Cost\", \"0.0\", \"d2^True\");");
    _sleep(1000);
    
    net->SetPChance("h3^False h3^True", "0.9 0.1", "h2^False d2^False");
    printf("\n net->SetPChance(\"h3^False h3^True\", \"0.9 0.1\", \"h2^False d2^False\");");
    _sleep(1000);
    
    net->SetPChance("h3^False h3^True", "0.5 0.5", "h2^False d2^True");
    printf("\n net->SetPChance(\"h3^False h3^True\", \"0.5 0.5\", \"h2^False d2^True\");");
    _sleep(1000);
    
    net->SetPChance("h3^False h3^True", "0.8 0.2", "h2^True d2^False");
    printf("\n net->SetPChance(\"h3^False h3^True\", \"0.8 0.2\", \"h2^True d2^False\");");
    _sleep(1000);
    
    net->SetPChance("h3^False h3^True", "0.1 0.9", "h2^True d2^True");
    printf("\n net->SetPChance(\"h3^False h3^True\", \"0.1 0.9\", \"h2^True d2^True\");");
    _sleep(1000);
    
    net->SetPChance("t3^False t3^True", "0.1 0.9", "h3^False");
    printf("\n net->SetPChance(\"t3^False t3^True\", \"0.1 0.9\", \"h3^False\");");
    _sleep(1000);
    
    net->SetPChance("t3^False t3^True", "0.8 0.2", "h3^True");
    printf("\n net->SetPChance(\"t3^False t3^True\", \"0.8 0.2\", \"h3^True\");");
    _sleep(1000);
    
    net->SetPDecision("d3^False d3^True", "0.5 0.5", "t3^False");
    printf("\n net->SetPDecision(\"d3^False d3^True\", \"0.5 0.5\", \"t3^False\");");
    _sleep(1000);
    
    net->SetPDecision("d3^False d3^True", "0.5 0.5", "t3^True");
    printf("\n net->SetPDecision(\"d3^False d3^True\", \"0.5 0.5\", \"t3^True\");");
    _sleep(1000);
    
    net->SetValueCost("u3^Cost", "-100.0", "d3^False");
    printf("\n net->SetValueCost(\"u3^Cost\", \"-100.0\", \"d3^False\");");
    _sleep(1000);
    
    net->SetValueCost("u3^Cost", "0.0", "d3^True");
    printf("\n net->SetValueCost(\"u3^Cost\", \"0.0\", \"d3^True\");");
    _sleep(1000);
    
    net->SetPChance("h4^False h4^True", "0.9 0.1", "h3^False d3^False");
    printf("\n net->SetPChance(\"h4^False h4^True\", \"0.9 0.1\", \"h3^False d3^False\");");
    _sleep(1000);
    
    net->SetPChance("h4^False h4^True", "0.8 0.2", "h3^False d3^True");
    printf("\n net->SetPChance(\"h4^False h4^True\", \"0.8 0.2\", \"h3^False d3^True\");");
    _sleep(1000);
    
    net->SetPChance("h4^False h4^True", "0.5 0.5", "h3^True d3^False");
    printf("\n net->SetPChance(\"h4^False h4^True\", \"0.5 0.5\", \"h3^True d3^False\");");
    _sleep(1000);
    
    net->SetPChance("h4^False h4^True", "0.1 0.9", "h3^True d3^True");
    printf("\n net->SetPChance(\"h4^False h4^True\", \"0.1 0.9\", \"h3^True d3^True\");");
    _sleep(1000);
    
    net->SetValueCost("u4^Cost", "1000.0", "h4^False");
    printf("\n net->SetValueCost(\"u4^Cost\", \"1000.0\", \"h4^False\");");
    _sleep(1000);
    
    net->SetValueCost("u4^Cost", "300.0", "h4^True");
    printf("\n net->SetValueCost(\"u4^Cost\", \"300.0\", \"h4^True\");");

    textcolor(LIGHTGREEN);
    printf("\n ......All distributions are added....\n");
    textcolor(WHITE);
    getch();

    return net;
}


BayesNet *ScalarGaussianBNetModel()
{
    // NodeA  NodeB 
    //     \ /
    //    NodeC
    //     / \
    // NodeD  NodeE

    BayesNet *net;
    net = new BayesNet();

    textcolor(WHITE);
    net->AddNode(continuous^"NodeA NodeB NodeC", "dim1");
    printf("\n net->AddNode(continuous^\"NodeA NodeB NodeC\", \"dim1\");");
    textcolor(LIGHTGREEN);

    printf("\t\t\t\tAdding of nodes is in process....");
    _sleep(2000);
    textcolor(WHITE);

    net->AddNode(continuous^"NodeD NodeE", "dim1");
    printf("\n net->AddNode(continuous^\"NodeD NodeE\", \"dim1\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All nodes are added....\n");
    getch();

    // arcs
    textcolor(WHITE);
    net->AddArc("NodeA NodeB", "NodeC");
    printf("\n net->AddArc(\"NodeA NodeB\", \"NodeC\");");
    
    textcolor(LIGHTGREEN);
    printf("\t\t\t\t\t\tAdding of arcs is in process....");
    _sleep(2000);

    textcolor(WHITE);
    
    net->AddArc("NodeC", "NodeD NodeE");
    printf("\n net->AddArc(\"NodeC\", \"NodeD NodeE\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All arcs are added....\n");
    getch();
    // distributions
    textcolor(WHITE);

    net->SetPGaussian("NodeA", "1.0", "4.0");
    printf("\n net->SetPGaussian(\"NodeA\", \"1.0\", \"4.0\");");
    textcolor(LIGHTGREEN);
    printf("\t\t\t\t\tAdding of distributions is in process....");
    _sleep(2000);

    textcolor(WHITE);

    net->SetPGaussian("NodeB", "1.0", "1.0");
    printf("\n net->SetPGaussian(\"NodeB\", \"1.0\", \"1.0\");");
    _sleep(1000);

    net->SetPGaussian("NodeC", "0.0", "2.0", "1.0 2.0");
    printf("\n net->SetPGaussian(\"NodeC\", \"0.0\", \"2.0\", \"1.0 2.0\");");
    _sleep(1000);

    net->SetPGaussian("NodeD", "0.0", "4.0", "1.1");
    printf("\n net->SetPGaussian(\"NodeD\", \"0.0\", \"4.0\", \"1.1\");");
    _sleep(1000);

    net->SetPGaussian("NodeE", "-0.8", "1.2", "2.0");
    printf("\n net->SetPGaussian(\"NodeE\", \"-0.8\", \"1.2\", \"2.0\");");
    textcolor(LIGHTGREEN);
    printf("\n ......All distributions are added....\n");
    textcolor(WHITE);

    return net;
}

BayesNet *WasteModel()
{
    BayesNet *net;
    net = new BayesNet();

    textcolor(WHITE);

    net->AddNode(discrete^"node0 node1 node3", "True False");
    printf("\n net->AddNode(discrete^\"node0 node1 node3\", \"True False\");");
    textcolor(LIGHTGREEN);

    printf("\t\t\t\tAdding of nodes is in process....");
    _sleep(2000);
    textcolor(WHITE);
    
    net->AddNode(continuous^"node2 node4 node5 node6 node7 node8", "dim1");
    printf("\n net->AddNode(continuous^\"node2 node4 node5 node6 node7 node8\", \"dim1\");");
    _sleep(1000);

    textcolor(LIGHTGREEN);
    printf("\n ......All nodes are added....\n");
    getch();

    // arcs
    textcolor(WHITE);
    net->AddArc("node0 node1", "node2");
    printf("\n net->AddArc(\"node0 node1\", \"node2\");");

    textcolor(LIGHTGREEN);
    printf("\t\t\t\t\t\t\tAdding of arcs is in process....");
    _sleep(2000);

    textcolor(WHITE);

       
    net->AddArc("node1 node2 node3", "node5") ;
    printf("\n net->AddArc(\"node1 node2 node3\", \"node5\") ;");
    _sleep(1000);

    net->AddArc( "node1", "node6");
    printf("\n net->AddArc( \"node1\", \"node6\");");
    _sleep(1000);

    net->AddArc( "node3", "node4");
    printf("\n net->AddArc( \"node3\", \"node4\");");
    _sleep(1000);
    
    net->AddArc( "node5 node6", "node7");
    printf("\n net->AddArc( \"node5 node6\", \"node7\");");
    _sleep(1000);
    
    net->AddArc( "node6", "node8");
    printf("\n net->AddArc( \"node6\", \"node8\");");
    _sleep(1000);
    textcolor(LIGHTGREEN);
    printf("\n ......All arcs are added....\n");
    getch();
    // distributions
    textcolor(WHITE);
    
    net->SetPTabular( "node0^False node0^True", "0.95 0.05");
    printf("\n net->SetPTabular( \"node0^False node0^True\", \"0.95 0.05\");");
    textcolor(LIGHTGREEN);
    printf("\t\t\t\tAdding of distributions is in process....");
    _sleep(2000);

    textcolor(WHITE);

    net->SetPTabular( "node1^False node1^True", "0.285714 0.714286");
    printf("\n net->SetPTabular( \"node1^False node1^True\", \"0.285714 0.714286\");");
    _sleep(1000);

    net->SetPTabular( "node3^False node3^True", "0.85 0.15");
    printf("\n net->SetPTabular( \"node3^False node3^True\", \"0.85 0.15\");");
    _sleep(1000);

    net->SetPGaussian( "node2", "-3.2", "0.00002", "", "node0^False node1^True");
    printf("\n net->SetPGaussian( \"node2\", \"-3.2\", \"0.00002\", \"\", \"node0^False node1^True\");");
    _sleep(1000);

    net->SetPGaussian( "node2", "-0.5", "0.0001", "", "node0^False node1^False");
    printf("\n net->SetPGaussian( \"node2\", \"-0.5\", \"0.0001\", \"\", \"node0^False node1^False\");");
    _sleep(1000);

    net->SetPGaussian( "node2", "-3.9", "0.00002", "", "node0^True node1^True");
    printf("\n net->SetPGaussian( \"node2\", \"-3.9\", \"0.00002\", \"\", \"node0^True node1^True\");");
    _sleep(1000);

    net->SetPGaussian( "node2", "-0.4", "0.0001", "", "node0^True node1^False");
    printf("\n net->SetPGaussian( \"node2\", \"-0.4\", \"0.0001\", \"\", \"node0^True node1^False\");");
    _sleep(1000);


    net->SetPGaussian( "node4", "-2", "0.1", "", "node3^False");
    printf("\n net->SetPGaussian( \"node4\", \"-2\", \"0.1\", \"\", \"node3^False\");");
    _sleep(1000);

    net->SetPGaussian( "node4", "-1", "0.3", "", "node3^True");
    printf("\n net->SetPGaussian( \"node4\", \"-1\", \"0.3\", \"\", \"node3^True\");");
    _sleep(1000);


    net->SetPGaussian( "node5", "6.5", "0.03", "1.0", "node1^False node3^False");
    printf("\n net->SetPGaussian( \"node5\", \"6.5\", \"0.03\", \"1.0\", \"node1^False node3^False\");");
    _sleep(1000);

    net->SetPGaussian( "node5", "7.5", "0.1", "1.0", "node1^False node3^True");
    printf("\n net->SetPGaussian( \"node5\", \"7.5\", \"0.1\", \"1.0\", \"node1^False node3^True\");");
    _sleep(1000);

    net->SetPGaussian( "node5", "6.0", "0.04", "1.0", "node1^True node3^False");
    printf("\n net->SetPGaussian( \"node5\", \"6.0\", \"0.04\", \"1.0\", \"node1^True node3^False\");");
    _sleep(1000);

    net->SetPGaussian( "node5", "7.0", "0.01", "1.0", "node1^True node3^True");
    printf("\n net->SetPGaussian( \"node5\", \"7.0\", \"0.01\", \"1.0\", \"node1^True node3^True\");");
    _sleep(1000);


    net->SetPGaussian( "node6", "0.5", "0.01", "", "node1^False");
    printf("\n net->SetPGaussian( \"node6\", \"0.5\", \"0.01\", \"\", \"node1^False\");");
    _sleep(1000);

    net->SetPGaussian( "node6", "-0.5", "0.005", "", "node1^True");
    printf("\n net->SetPGaussian( \"node6\", \"-0.5\", \"0.005\", \"\", \"node1^True\");");
    _sleep(1000);


    net->SetPGaussian( "node7", "0.0", "0.02", "1.0 1.0");
    printf("\n net->SetPGaussian( \"node7\", \"0.0\", \"0.02\", \"1.0 1.0\");");
    _sleep(1000);

    net->SetPGaussian( "node8", "3.0", "0.25", "-0.5");
    printf("\n net->SetPGaussian( \"node8\", \"3.0\", \"0.25\", \"-0.5\");");
    _sleep(1000);
    textcolor(LIGHTGREEN);
    printf("\n ......All distributions are added....\n");
    textcolor(WHITE);


    return net;
}



PNLW_END