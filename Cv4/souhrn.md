1. Splněno - Využívám matici `modelMatrix`
2. Splněno - Třídě `DrawableObject` jde přířadit transformace pomocí `setTransformation()`
3. Splněno - Pomocí transformace `rotateDynamic` bude objekt neustále rotovat
4. Splněno - Pokud provedu první rotaci, bude potom i osa X otočená. Když pak objekt posunu, nepůjde doprava, ale podél té otočené osy
5. Nesplněno? - Můžu sice individuální transformace seskupovat a kombinovat, nemám ale žádný rozdíl mezi skupinou a listem, ani společný interface.
6. Splněno - Les se generuje náhodně
7. Splněno - Slunce je oprostřed obrazovky. Země je posunutá a točí se kolem středu. Měsíc se točí kolem země.