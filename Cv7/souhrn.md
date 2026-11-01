1. Splněno - Převody jsem demonstroval na neuniformě škálované kouli ať jde rozdíl lépe vidět.
   1. (a) Správný převod pomocí inverzní transponované modelové matice (normálová matice)
   2. (b) Nesprávný převod pomocí pouze modelové matice. Normály nezůstávají kolmé
   3. (c) Bez převodu. Normály zůstávají v lokálním souřadnicovém systému
2. Splněno
   1. Zrcadlová složka se zobrazuje na odvrácené straně koule, protože výpočet zrcadlové složky funguje ikdyž je normála obrácená
   2. Přidal jsem kontrolu, která nastaví sílu zrcadlové složky na nulu, pokud je světlo přichází ze zadní strany povrchu
   3. Při změně velikosti okne se musí přepočítat poměr stran. Ten se používá pro vytvoření projekční matice
3. Splněno - Pro útlum světla využívám hodnoty konstantní (1.0), lineární (0.09) a kvadratické (0.032)