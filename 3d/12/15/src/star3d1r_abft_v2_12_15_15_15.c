/* star3d1r_abft_v2_12_15_15_15.c
 * 
 * Code generation of the following Alpha system:
 *	 affine star3d1r_abft_v2_12_15_15_15 [T, N] -> {  : T >= 10 and N >= 20 }
 *	 	inputs
 *	 		X : {[i, j, k]: 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	outputs
 *	 		Y : {[t, i, j, k]: 0 <= t <= T and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N }
 *	 	locals
 *	 		W : {[i, j, k]: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 }
 *	 		C1 : {[tt, ti, tj, tk]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N }
 *	 		C2 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p <= 2 and -2 <= q <= 2 and -2 <= r <= 2 }
 *	 		I : {[tt, ti, tj, tk]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N }
 *	 		WKernel : {[i, j, k]: -2 <= i <= 2 and -2 <= j <= 2 and -2 <= k <= 2 }
 *	 		WCombos : {[i, j, k]: -2 <= i <= 2 and -2 <= j <= 2 and -2 <= k <= 2 }
 *	 		WAll : {[w]: 0 < w <= 12 }
 *	 		C2_NR : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and -2 <= r < 0 }
 *	 		C2_NR2 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and -2 <= r < 0 }
 *	 		C2_NR3 : {[tt, ti, tj, tk, p, q, r]: p = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and -2 <= r < 0 }
 *	 		C2_NR4 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and -2 <= r < 0 }
 *	 		C2_NR5 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and -2 <= r < 0 }
 *	 		C2_NR6 : {[tt, ti, tj, tk, p, q, r]: p = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and -2 <= r < 0 }
 *	 		C2_NR7 : {[tt, ti, tj, tk, p, q, r]: q = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= r < 0 }
 *	 		C2_NR8 : {[tt, ti, tj, tk, p, q, r]: q = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= r < 0 }
 *	 		C2_NR9 : {[tt, ti, tj, tk, p, q, r]: p = 0 and q = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= r < 0 }
 *	 		C2_NR10 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and 0 < r <= 2 }
 *	 		C2_NR11 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and 0 < r <= 2 }
 *	 		C2_NR12 : {[tt, ti, tj, tk, p, q, r]: p = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and 0 < r <= 2 }
 *	 		C2_NR13 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and 0 < r <= 2 }
 *	 		C2_NR14 : {[tt, ti, tj, tk, p, q, r]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and 0 < r <= 2 }
 *	 		C2_NR15 : {[tt, ti, tj, tk, p, q, r]: p = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and 0 < r <= 2 }
 *	 		C2_NR16 : {[tt, ti, tj, tk, p, q, r]: q = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < r <= 2 }
 *	 		C2_NR17 : {[tt, ti, tj, tk, p, q, r]: q = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < r <= 2 }
 *	 		C2_NR18 : {[tt, ti, tj, tk, p, q, r]: p = 0 and q = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < r <= 2 }
 *	 		C2_NR19 : {[tt, ti, tj, tk, p, q, r]: r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 }
 *	 		C2_NR20 : {[tt, ti, tj, tk, p, q, r]: r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 }
 *	 		C2_NR21 : {[tt, ti, tj, tk, p, q, r]: p = 0 and r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 }
 *	 		C2_NR22 : {[tt, ti, tj, tk, p, q, r]: r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 }
 *	 		C2_NR23 : {[tt, ti, tj, tk, p, q, r]: r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 }
 *	 		C2_NR24 : {[tt, ti, tj, tk, p, q, r]: p = 0 and r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 }
 *	 		C2_NR25 : {[tt, ti, tj, tk, p, q, r]: q = 0 and r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 }
 *	 		C2_NR26 : {[tt, ti, tj, tk, p, q, r]: q = 0 and r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 }
 *	 		C2_NR27 : {[tt, ti, tj, tk, p, q, r]: p = 0 and q = 0 and r = 0 and tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N }
 *	 		I_NR : {[tt, ti, tj, tk]: tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N }
 *	 	when {  : T >= 10 and N >= 20 } let
 *	 		Y[t,i,j,k] = case  {
 *	 			{: 0 <= t <= 1 } : X[i,j,k];
 *	 			{: k = N and t >= 2  or  j = N and t >= 2  or  i = N and t >= 2  or  k = 0 and t >= 2  or  j = 0 and t >= 2  or  i = 0 and t >= 2 } : Y[t-1,i,j,k];
 *	 			{: t >= 2 and 0 < i < N and 0 < j < N and 0 < k < N } : (((((((0.25[] * Y[t-1,i,j,k]) + (0.1248[] * Y[t-1,i-1,j,k])) + (0.1249[] * Y[t-1,i+1,j,k])) + (0.125[] * Y[t-1,i,j-1,k])) + (0.125[] * Y[t-1,i,j+1,k])) + (0.1251[] * Y[t-1,i,j,k-1])) + (0.1252[] * Y[t-1,i,j,k+1]));
 *	 		};
 *	 		
 *	 		W[i,j,k] = case  {
 *	 			{: i = 1 and j = 0 and k = 0 } : 0.1249[];
 *	 			{: i = 0 and j = -1 and k = 0 } : 0.125[];
 *	 			{: i = 0 and j = 0 and k = 1 } : 0.1252[];
 *	 			{: i = -1 and j = 0 and k = 0 } : 0.1248[];
 *	 			{: i = 0 and j = 1 and k = 0 } : 0.125[];
 *	 			{: i = 0 and j = 0 and k = -1 } : 0.1251[];
 *	 			{: i = 0 and j = 0 and k = 0 } : 0.25[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		WKernel[i,j,k] = case  {
 *	 			{: -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1 } : 1[];
 *	 			auto : 0[];
 *	 		};
 *	 		
 *	 		WCombos[i,j,k] = reduce(+, (i,j,k,p,q,r->i,j,k), (WKernel[i-p,j-q,k-r] * W[p,q,r]));
 *	 		
 *	 		WAll[w] = case  {
 *	 			{: w = 1 } : 1[];
 *	 			{: w >= 2 } : (WAll[w-1] * WCombos[0,0,0]);
 *	 		};
 *	 		
 *	 		C1[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,i,j,k->tt,ti,tj,tk), {: 15ti <= i <= 38 + 15ti and 15tj <= j <= 38 + 15tj and 15tk <= k <= 38 + 15tk } : Y[12tt,i,j,k]);
 *	 		
 *	 		C2[tt,ti,tj,tk,p,q,r] = case  {
 *	 			(WCombos[p,q,r] * C2_NR);
 *	 			(WCombos[p,q,r] * C2_NR2);
 *	 			(WCombos[p,q,r] * C2_NR3);
 *	 			(WCombos[p,q,r] * C2_NR4);
 *	 			(WCombos[p,q,r] * C2_NR5);
 *	 			(WCombos[p,q,r] * C2_NR6);
 *	 			(WCombos[p,q,r] * C2_NR7);
 *	 			(WCombos[p,q,r] * C2_NR8);
 *	 			(WCombos[p,q,r] * C2_NR9);
 *	 			(WCombos[p,q,r] * C2_NR10);
 *	 			(WCombos[p,q,r] * C2_NR11);
 *	 			(WCombos[p,q,r] * C2_NR12);
 *	 			(WCombos[p,q,r] * C2_NR13);
 *	 			(WCombos[p,q,r] * C2_NR14);
 *	 			(WCombos[p,q,r] * C2_NR15);
 *	 			(WCombos[p,q,r] * C2_NR16);
 *	 			(WCombos[p,q,r] * C2_NR17);
 *	 			(WCombos[p,q,r] * C2_NR18);
 *	 			(WCombos[p,q,r] * C2_NR19);
 *	 			(WCombos[p,q,r] * C2_NR20);
 *	 			(WCombos[p,q,r] * C2_NR21);
 *	 			(WCombos[p,q,r] * C2_NR22);
 *	 			(WCombos[p,q,r] * C2_NR23);
 *	 			(WCombos[p,q,r] * C2_NR24);
 *	 			(WCombos[p,q,r] * C2_NR25);
 *	 			(WCombos[p,q,r] * C2_NR26);
 *	 			(WCombos[p,q,r] * C2_NR27);
 *	 		};
 *	 		
 *	 		I[tt,ti,tj,tk] = ((I_NR - C1) / C1);
 *	 		
 *	 		C2_NR[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p+w,15tj+q+w,15tk+r+w]));
 *	 		
 *	 		C2_NR2[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p-w+38,15tj+q+w,15tk+r+w]));
 *	 		
 *	 		C2_NR3[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w } : (WAll[w] * Y[12tt-w,i,15tj+q+w,15tk+r+w]));
 *	 		
 *	 		C2_NR4[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p+w,15tj+q-w+38,15tk+r+w]));
 *	 		
 *	 		C2_NR5[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p-w+38,15tj+q-w+38,15tk+r+w]));
 *	 		
 *	 		C2_NR6[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w } : (WAll[w] * Y[12tt-w,i,15tj+q-w+38,15tk+r+w]));
 *	 		
 *	 		C2_NR7[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,j->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w } : (WAll[w] * Y[12tt-w,15ti+p+w,j,15tk+r+w]));
 *	 		
 *	 		C2_NR8[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,j->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w } : (WAll[w] * Y[12tt-w,15ti+p-w+38,j,15tk+r+w]));
 *	 		
 *	 		C2_NR9[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i,j->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tj + w <= j <= 38 + 15tj - w } : (WAll[w] * Y[12tt-w,i,j,15tk+r+w]));
 *	 		
 *	 		C2_NR10[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p+w,15tj+q+w,15tk+r-w+38]));
 *	 		
 *	 		C2_NR11[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p-w+38,15tj+q+w,15tk+r-w+38]));
 *	 		
 *	 		C2_NR12[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w } : (WAll[w] * Y[12tt-w,i,15tj+q+w,15tk+r-w+38]));
 *	 		
 *	 		C2_NR13[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p+w,15tj+q-w+38,15tk+r-w+38]));
 *	 		
 *	 		C2_NR14[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w->tt,ti,tj,tk,p,q,r), (WAll[w] * Y[12tt-w,15ti+p-w+38,15tj+q-w+38,15tk+r-w+38]));
 *	 		
 *	 		C2_NR15[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w } : (WAll[w] * Y[12tt-w,i,15tj+q-w+38,15tk+r-w+38]));
 *	 		
 *	 		C2_NR16[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,j->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w } : (WAll[w] * Y[12tt-w,15ti+p+w,j,15tk+r-w+38]));
 *	 		
 *	 		C2_NR17[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,j->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w } : (WAll[w] * Y[12tt-w,15ti+p-w+38,j,15tk+r-w+38]));
 *	 		
 *	 		C2_NR18[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i,j->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tj + w <= j <= 38 + 15tj - w } : (WAll[w] * Y[12tt-w,i,j,15tk+r-w+38]));
 *	 		
 *	 		C2_NR19[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,15ti+p+w,15tj+q+w,k]));
 *	 		
 *	 		C2_NR20[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,15ti+p-w+38,15tj+q+w,k]));
 *	 		
 *	 		C2_NR21[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,i,15tj+q+w,k]));
 *	 		
 *	 		C2_NR22[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,15ti+p+w,15tj+q-w+38,k]));
 *	 		
 *	 		C2_NR23[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,15ti+p-w+38,15tj+q-w+38,k]));
 *	 		
 *	 		C2_NR24[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,i,15tj+q-w+38,k]));
 *	 		
 *	 		C2_NR25[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,j,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,15ti+p+w,j,k]));
 *	 		
 *	 		C2_NR26[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,j,k->tt,ti,tj,tk,p,q,r), {: 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w and 15tk + w <= k <= 38 + 15tk - w } : (WAll[w] * Y[12tt-w,15ti+p-w+38,j,k]));
 *	 		
 *	 		C2_NR27[tt,ti,tj,tk,p,q,r] = reduce(+, (tt,ti,tj,tk,p,q,r,w,i,j,k->tt,ti,tj,tk,p,q,r), {: w = 12 and 12 + 15ti <= i <= 26 + 15ti and 12 + 15tj <= j <= 26 + 15tj and 12 + 15tk <= k <= 26 + 15tk } : (WAll[w] * Y[12tt-w,i,j,k]));
 *	 		
 *	 		I_NR[tt,ti,tj,tk] = reduce(+, (tt,ti,tj,tk,p,q,r->tt,ti,tj,tk), C2);
 *	 .
 *
 * Uses the memory map:
 *	 C2_NR(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR10(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR11(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR12(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,q,r)
 *	 C2_NR13(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR14(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR15(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,q,r)
 *	 C2_NR16(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,0,r)
 *	 C2_NR17(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,0,r)
 *	 C2_NR18(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,0,r)
 *	 C2_NR19(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,0)
 *	 C2_NR2(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR20(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,0)
 *	 C2_NR21(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,q,0)
 *	 C2_NR22(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,0)
 *	 C2_NR23(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,0)
 *	 C2_NR24(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,q,0)
 *	 C2_NR25(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,0,0)
 *	 C2_NR26(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,0,0)
 *	 C2_NR27(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,0,0)
 *	 C2_NR3(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,q,r)
 *	 C2_NR4(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR5(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,q,r)
 *	 C2_NR6(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,q,r)
 *	 C2_NR7(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,0,r)
 *	 C2_NR8(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,p,0,r)
 *	 C2_NR9(tt,ti,tj,tk,p,q,r) -> C2(tt,ti,tj,tk,0,0,r)
 *	 Y(t,i,j,k) -> Y(t - 2*floord(t, 2),i,j,k)
 *
 * Implements the schedule:
 *   child:
 *     sequence:
 *     - filter: "{ SW[i,j,k] }"
 *     - filter: "{ SWKernel[i,j,k] }"
 *     - filter: "{ SWCombos[i,j,k,p,q,r] }"
 *     - filter: "{ SWAll[w] }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { SWAll[w]->[w] } \
 *         ]"
 *     - filter: "{ \
 *         SY_cb0[t,i,j,k]; \
 *         SY_cb1[t,i,j,k]; \
 *         SY_cb2[t,i,j,k]; \
 *         SC1[tt,ti,tj,tk,i,j,k]; \
 *         SC2_NR[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR2[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR3[tt,ti,tj,tk,p,q,r,w,i]; \
 *         SC2_NR4[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR5[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR6[tt,ti,tj,tk,p,q,r,w,i]; \
 *         SC2_NR7[tt,ti,tj,tk,p,q,r,w,j]; \
 *         SC2_NR8[tt,ti,tj,tk,p,q,r,w,j]; \
 *         SC2_NR9[tt,ti,tj,tk,p,q,r,w,i,j]; \
 *         SC2_NR10[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR11[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR12[tt,ti,tj,tk,p,q,r,w,i]; \
 *         SC2_NR13[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR14[tt,ti,tj,tk,p,q,r,w]; \
 *         SC2_NR15[tt,ti,tj,tk,p,q,r,w,i]; \
 *         SC2_NR16[tt,ti,tj,tk,p,q,r,w,j]; \
 *         SC2_NR17[tt,ti,tj,tk,p,q,r,w,j]; \
 *         SC2_NR18[tt,ti,tj,tk,p,q,r,w,i,j]; \
 *         SC2_NR19[tt,ti,tj,tk,p,q,r,w,k]; \
 *         SC2_NR20[tt,ti,tj,tk,p,q,r,w,k]; \
 *         SC2_NR21[tt,ti,tj,tk,p,q,r,w,i,k]; \
 *         SC2_NR22[tt,ti,tj,tk,p,q,r,w,k]; \
 *         SC2_NR23[tt,ti,tj,tk,p,q,r,w,k]; \
 *         SC2_NR24[tt,ti,tj,tk,p,q,r,w,i,k]; \
 *         SC2_NR25[tt,ti,tj,tk,p,q,r,w,j,k]; \
 *         SC2_NR26[tt,ti,tj,tk,p,q,r,w,j,k]; \
 *         SC2_NR27[tt,ti,tj,tk,p,q,r,w,i,j,k]; \
 *         SC2_cb0[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb1[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb2[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb3[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb4[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb5[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb6[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb7[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb8[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb9[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb10[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb11[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb12[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb13[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb14[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb15[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb16[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb17[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb18[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb19[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb20[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb21[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb22[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb23[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb24[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb25[tt,ti,tj,tk,p,q,r]; \
 *         SC2_cb26[tt,ti,tj,tk,p,q,r]; \
 *         SI_NR[tt,ti,tj,tk,p,q,r]; \
 *         SI[tt,ti,tj,tk] \
 *       }"
 *       child:
 *         schedule: "[T,N]->[\
 *           { \
 *             SY_cb0[t,i,j,k]->[t]; \
 *             SY_cb1[t,i,j,k]->[t]; \
 *             SY_cb2[t,i,j,k]->[t]; \
 *             SC1[tt,ti,tj,tk,i,j,k]->[12tt]; \
 *             SC2_cb0[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb1[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb2[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb3[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb4[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb5[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb6[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb7[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb8[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb9[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb10[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb11[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb12[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb13[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb14[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb15[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb16[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb17[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb18[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb19[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb20[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb21[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb22[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb23[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb24[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb25[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_cb26[tt,ti,tj,tk,p,q,r]->[12tt]; \
 *             SC2_NR[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR2[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR3[tt,ti,tj,tk,p,q,r,w,i]->[12tt-w]; \
 *             SC2_NR4[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR5[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR6[tt,ti,tj,tk,p,q,r,w,i]->[12tt-w]; \
 *             SC2_NR7[tt,ti,tj,tk,p,q,r,w,j]->[12tt-w]; \
 *             SC2_NR8[tt,ti,tj,tk,p,q,r,w,j]->[12tt-w]; \
 *             SC2_NR9[tt,ti,tj,tk,p,q,r,w,i,j]->[12tt-w]; \
 *             SC2_NR10[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR11[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR12[tt,ti,tj,tk,p,q,r,w,i]->[12tt-w]; \
 *             SC2_NR13[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR14[tt,ti,tj,tk,p,q,r,w]->[12tt-w]; \
 *             SC2_NR15[tt,ti,tj,tk,p,q,r,w,i]->[12tt-w]; \
 *             SC2_NR16[tt,ti,tj,tk,p,q,r,w,j]->[12tt-w]; \
 *             SC2_NR17[tt,ti,tj,tk,p,q,r,w,j]->[12tt-w]; \
 *             SC2_NR18[tt,ti,tj,tk,p,q,r,w,i,j]->[12tt-w]; \
 *             SC2_NR19[tt,ti,tj,tk,p,q,r,w,k]->[12tt-w]; \
 *             SC2_NR20[tt,ti,tj,tk,p,q,r,w,k]->[12tt-w]; \
 *             SC2_NR21[tt,ti,tj,tk,p,q,r,w,i,k]->[12tt-w]; \
 *             SC2_NR22[tt,ti,tj,tk,p,q,r,w,k]->[12tt-w]; \
 *             SC2_NR23[tt,ti,tj,tk,p,q,r,w,k]->[12tt-w]; \
 *             SC2_NR24[tt,ti,tj,tk,p,q,r,w,i,k]->[12tt-w]; \
 *             SC2_NR25[tt,ti,tj,tk,p,q,r,w,j,k]->[12tt-w]; \
 *             SC2_NR26[tt,ti,tj,tk,p,q,r,w,j,k]->[12tt-w]; \
 *             SC2_NR27[tt,ti,tj,tk,p,q,r,w,i,j,k]->[12tt-w]; \
 *             SI[tt,ti,tj,tk]->[12tt]; \
 *             SI_NR[tt,ti,tj,tk,p,q,r]->[12tt] \
 *           } \
 *         ]"
 *         child:
 *           sequence:
 *           - filter: "{ SY_cb0[t,i,j,k]; SY_cb1[t,i,j,k]; SY_cb2[t,i,j,k] }"
 *           - filter: "{ SC1[tt,ti,tj,tk,i,j,k]; SC2_NR[tt,ti,tj,tk,p,q,r,w]; SC2_NR2[tt,ti,tj,tk,p,q,r,w]; SC2_NR3[tt,ti,tj,tk,p,q,r,w,i]; SC2_NR4[tt,ti,tj,tk,p,q,r,w]; SC2_NR5[tt,ti,tj,tk,p,q,r,w]; SC2_NR6[tt,ti,tj,tk,p,q,r,w,i]; SC2_NR7[tt,ti,tj,tk,p,q,r,w,j]; SC2_NR8[tt,ti,tj,tk,p,q,r,w,j]; SC2_NR9[tt,ti,tj,tk,p,q,r,w,i,j]; SC2_NR10[tt,ti,tj,tk,p,q,r,w]; SC2_NR11[tt,ti,tj,tk,p,q,r,w]; SC2_NR12[tt,ti,tj,tk,p,q,r,w,i]; SC2_NR13[tt,ti,tj,tk,p,q,r,w]; SC2_NR14[tt,ti,tj,tk,p,q,r,w]; SC2_NR15[tt,ti,tj,tk,p,q,r,w,i]; SC2_NR16[tt,ti,tj,tk,p,q,r,w,j]; SC2_NR17[tt,ti,tj,tk,p,q,r,w,j]; SC2_NR18[tt,ti,tj,tk,p,q,r,w,i,j]; SC2_NR19[tt,ti,tj,tk,p,q,r,w,k]; SC2_NR20[tt,ti,tj,tk,p,q,r,w,k]; SC2_NR21[tt,ti,tj,tk,p,q,r,w,i,k]; SC2_NR22[tt,ti,tj,tk,p,q,r,w,k]; SC2_NR23[tt,ti,tj,tk,p,q,r,w,k]; SC2_NR24[tt,ti,tj,tk,p,q,r,w,i,k]; SC2_NR25[tt,ti,tj,tk,p,q,r,w,j,k]; SC2_NR26[tt,ti,tj,tk,p,q,r,w,j,k]; SC2_NR27[tt,ti,tj,tk,p,q,r,w,i,j,k] }"
 *           - filter: "{ SC2_cb0[tt,ti,tj,tk,p,q,r]; SC2_cb1[tt,ti,tj,tk,p,q,r]; SC2_cb2[tt,ti,tj,tk,p,q,r]; SC2_cb3[tt,ti,tj,tk,p,q,r]; SC2_cb4[tt,ti,tj,tk,p,q,r]; SC2_cb5[tt,ti,tj,tk,p,q,r]; SC2_cb6[tt,ti,tj,tk,p,q,r]; SC2_cb7[tt,ti,tj,tk,p,q,r]; SC2_cb8[tt,ti,tj,tk,p,q,r]; SC2_cb9[tt,ti,tj,tk,p,q,r]; SC2_cb10[tt,ti,tj,tk,p,q,r]; SC2_cb11[tt,ti,tj,tk,p,q,r]; SC2_cb12[tt,ti,tj,tk,p,q,r]; SC2_cb13[tt,ti,tj,tk,p,q,r]; SC2_cb14[tt,ti,tj,tk,p,q,r]; SC2_cb15[tt,ti,tj,tk,p,q,r]; SC2_cb16[tt,ti,tj,tk,p,q,r]; SC2_cb17[tt,ti,tj,tk,p,q,r]; SC2_cb18[tt,ti,tj,tk,p,q,r]; SC2_cb19[tt,ti,tj,tk,p,q,r]; SC2_cb20[tt,ti,tj,tk,p,q,r]; SC2_cb21[tt,ti,tj,tk,p,q,r]; SC2_cb22[tt,ti,tj,tk,p,q,r]; SC2_cb23[tt,ti,tj,tk,p,q,r]; SC2_cb24[tt,ti,tj,tk,p,q,r]; SC2_cb25[tt,ti,tj,tk,p,q,r]; SC2_cb26[tt,ti,tj,tk,p,q,r] }"
 *           - filter: "{ SI_NR[tt,ti,tj,tk,p,q,r] }"
 *           - filter: "{ SI[tt,ti,tj,tk] }"
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define max(x, y)   ((x)>(y) ? (x) : (y))
#define min(x, y)   ((x)>(y) ? (y) : (x))
#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
#define mallocCheck(v,s,d) if ((v) == NULL) { printf("Failed to allocate memory for %s : size=%lu\n", "sizeof(d)*(s)", sizeof(d)*(s)); exit(-1); }
#define new_result() { .valid=0, .TP=0L, .FP=0L, .TN=0L, .FN=0L, .TPR=0.0f, .FPR=0.0f, .FNR=0.0f, .bit=0, .inj={.tt=0, .ti=0, .tj=0, .tk=0}, .result=0.0f, .noise=0.0f }

void initialize_timer();
void reset_timer();
void start_timer();
void stop_timer();
double elapsed_time();

struct INJ {
	int tt;
	int ti;
	int tj;
	int tk;
};

struct Result {
	int valid;
	long TP;
	long FP;
	long TN;
	long FN;
	float TPR;
	float FPR;
	float FNR;
	int bit;
	struct INJ inj;
	double result;
	double noise;
};

// Memory mapped targets
#define mem_X(i,j,k) X[(i)-(0)][(j)-(0)][(k)-(0)]
#define mem_Y(t,i,j,k) Y[(t)-(0)][(i)-(0)][(j)-(0)][(k)-(0)]
#define mem_W(i,j,k) W[(i)-(-1)][(j)-(-1)][(k)-(-1)]
#define mem_C1(tt,ti,tj,tk) C1[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)]
#define mem_C2(tt,ti,tj,tk,p,q,r) C2[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)][(p)-(-2)][(q)-(-2)][(r)-(-2)]
#define mem_I(tt,ti,tj,tk) I[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)]
#define mem_WKernel(i,j,k) WKernel[(i)-(-2)][(j)-(-2)][(k)-(-2)]
#define mem_WCombos(i,j,k) WCombos[(i)-(-2)][(j)-(-2)][(k)-(-2)]
#define mem_WAll(w) WAll[(w)-(1)]
#define mem_I_NR(tt,ti,tj,tk) I_NR[(tt)-(2)][(ti)-(1)][(tj)-(1)][(tk)-(1)]

// Memory access functions
#define X(i,j,k) mem_X(((i)),((j)),((k)))
#define Y(t,i,j,k) mem_Y(((t) - 2*floord((t), 2)),((i)),((j)),((k)))
#define W(i,j,k) mem_W(((i)),((j)),((k)))
#define C1(tt,ti,tj,tk) mem_C1(((tt)),((ti)),((tj)),((tk)))
#define C2(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define I(tt,ti,tj,tk) mem_I(((tt)),((ti)),((tj)),((tk)))
#define WKernel(i,j,k) mem_WKernel(((i)),((j)),((k)))
#define WCombos(i,j,k) mem_WCombos(((i)),((j)),((k)))
#define WAll(w) mem_WAll(((w)))
#define C2_NR(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR2(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR3(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),((q)),((r)))
#define C2_NR4(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR5(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR6(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),((q)),((r)))
#define C2_NR7(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),(0),((r)))
#define C2_NR8(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),(0),((r)))
#define C2_NR9(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),(0),((r)))
#define C2_NR10(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR11(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR12(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),((q)),((r)))
#define C2_NR13(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR14(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),((r)))
#define C2_NR15(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),((q)),((r)))
#define C2_NR16(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),(0),((r)))
#define C2_NR17(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),(0),((r)))
#define C2_NR18(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),(0),((r)))
#define C2_NR19(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),(0))
#define C2_NR20(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),(0))
#define C2_NR21(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),((q)),(0))
#define C2_NR22(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),(0))
#define C2_NR23(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),((q)),(0))
#define C2_NR24(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),((q)),(0))
#define C2_NR25(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),(0),(0))
#define C2_NR26(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),((p)),(0),(0))
#define C2_NR27(tt,ti,tj,tk,p,q,r) mem_C2(((tt)),((ti)),((tj)),((tk)),(0),(0),(0))
#define I_NR(tt,ti,tj,tk) mem_I_NR(((tt)),((ti)),((tj)),((tk)))

#ifdef ERROR_INJECTION
// Error injection harness
int tt_INJ;
int ti_INJ;
int tj_INJ;
int tk_INJ;
int BIT;

void inject_star3d1r_abft_v2_12_15_15_15(float *val) {
	int *bits;
	bits = (int*)val;
	*bits ^= 1 << BIT;
}
#endif

#if defined REPORT_COMPLEXITY_ONLY
void star3d1r_abft_v2_12_15_15_15(double T, double N, float ***X, float ****Y)
#else
struct Result star3d1r_abft_v2_12_15_15_15(long T, long N, float ***X, float ****Y)
#endif
{
	#if defined REPORT_COMPLEXITY_ONLY
	#undef ceild
	#undef floord
	#define ceild(n,d)  (double)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (double)floor(((double)(n))/((double)(d)))
	
	double Y_card = ((((double)-10) + T >= ((double)0) && ((double)-20) + N >= ((double)0)) ? (((((double)1) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double total_card = ((((double)-36) + T >= ((double)0) && ((double)-55) + N >= ((double)0)) ? (((((((double)9878800) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N) - ((double)4938219) * floord(T, ((double)12))) + (((double)-9876438) + ((double)4938219) * floord(T, ((double)12))) * floord(((double)5) + N, ((double)15)) + (((double)3292146) - ((double)1646073) * floord(T, ((double)12))) * floord(((double)5) + N, ((double)15))*floord(((double)5) + N, ((double)15)) + (((double)-365794) + ((double)182897) * floord(T, ((double)12))) * floord(((double)5) + N, ((double)15))*floord(((double)5) + N, ((double)15))*floord(((double)5) + N, ((double)15)))) : ((((double)-36) + T >= ((double)0) && ((double)-20) + N >= ((double)0) && ((double)54) - N >= ((double)0)) || (((double)-10) + T >= ((double)0) && ((double)35) - T >= ((double)0) && ((double)-20) + N >= ((double)0))) ? (((((double)2362) + T) + (((double)3) + ((double)3) * T) * N + (((double)3) + ((double)3) * T) * N*N + (((double)1) + T) * N*N*N)) : ((double)0));
	double expected_overhead = total_card / Y_card;
	printf("v2 (Y,C,overhead): %0.0lf,%0.0lf,%0.2lf\n", Y_card, total_card, expected_overhead);
	
	#undef ceild
	#undef floord
	#define ceild(n,d)  (int)ceil(((double)(n))/((double)(d)))
	#define floord(n,d) (int)floor(((double)(n))/((double)(d)))
	#else
	#if defined ERROR_INJECTION
	// Error injection configuration
	tt_INJ = getenv("tt_INJ") != NULL ? atoi(getenv("tt_INJ")) : -1;
	ti_INJ = getenv("ti_INJ") != NULL ? atoi(getenv("ti_INJ")) : -1;
	tj_INJ = getenv("tj_INJ") != NULL ? atoi(getenv("tj_INJ")) : -1;
	tk_INJ = getenv("tk_INJ") != NULL ? atoi(getenv("tk_INJ")) : -1;
	BIT = getenv("bit") != NULL ? atoi(getenv("bit")) : (int)(rand() % 32);
	#endif
		
	// Local memory allocation
	float* WAll = (float*)(calloc((12),sizeof(float)));
	
	float*** W = (float***)(calloc((3),sizeof(float**)));
	for (int i=0; i<(3); i++) {
		W[i] = (float**)(calloc((3),sizeof(float*)));
		for (int j=0; j<(3); j++) {
			W[i][j] = (float*)(calloc((3),sizeof(float)));
		}
	}
	
	float**** I_NR = (float****)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		I_NR[tt] = (float***)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			I_NR[tt][ti] = (float**)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				I_NR[tt][ti][tj] = (float*)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float)));
			}
		}
	}
	
	float**** I = (float****)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		I[tt] = (float***)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			I[tt][ti] = (float**)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				I[tt][ti][tj] = (float*)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float)));
			}
		}
	}
	
	float*** WKernel = (float***)(calloc((5),sizeof(float**)));
	for (int i=0; i<(5); i++) {
		WKernel[i] = (float**)(calloc((5),sizeof(float*)));
		for (int j=0; j<(5); j++) {
			WKernel[i][j] = (float*)(calloc((5),sizeof(float)));
		}
	}
	
	float**** C1 = (float****)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0),sizeof(float***)));
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		C1[tt] = (float***)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float**)));
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			C1[tt][ti] = (float**)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float*)));
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				C1[tt][ti][tj] = (float*)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float)));
			}
		}
	}
	
	float*** WCombos = (float***)(calloc((5),sizeof(float**)));
	for (int i=0; i<(5); i++) {
		WCombos[i] = (float**)(calloc((5),sizeof(float*)));
		for (int j=0; j<(5); j++) {
			WCombos[i][j] = (float*)(calloc((5),sizeof(float)));
		}
	}
	
	float******* C2 = (float*******)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0),sizeof(float******)));
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		C2[tt] = (float******)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float*****)));
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			C2[tt][ti] = (float*****)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float****)));
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				C2[tt][ti][tj] = (float****)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0),sizeof(float***)));
				for (int tk=0; tk<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tk++) {
					C2[tt][ti][tj][tk] = (float***)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0),sizeof(float**)));
					for (int p=0; p<((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0); p++) {
						C2[tt][ti][tj][tk][p] = (float**)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0),sizeof(float*)));
						for (int q=0; q<((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0); q++) {
							C2[tt][ti][tj][tk][p][q] = (float*)(calloc(((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0),sizeof(float)));
						}
					}
				}
			}
		}
	}

	#define SC1(tt,ti,tj,tk,i,j,k) C1(tt,ti,tj,tk) += Y((12*(tt)),((i)),((j)),((k)))
	#define SC2_NR(tt,ti,tj,tk,p,q,r,w) C2_NR(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),(15*(tj) + (q) + (w)),(15*(tk) + (r) + (w))))
	#define SC2_NR10(tt,ti,tj,tk,p,q,r,w) C2_NR10(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),(15*(tj) + (q) + (w)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR11(tt,ti,tj,tk,p,q,r,w) C2_NR11(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),(15*(tj) + (q) + (w)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR12(tt,ti,tj,tk,p,q,r,w,i) C2_NR12(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),(15*(tj) + (q) + (w)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR13(tt,ti,tj,tk,p,q,r,w) C2_NR13(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),(38 + 15*(tj) + (q) - (w)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR14(tt,ti,tj,tk,p,q,r,w) C2_NR14(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),(38 + 15*(tj) + (q) - (w)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR15(tt,ti,tj,tk,p,q,r,w,i) C2_NR15(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),(38 + 15*(tj) + (q) - (w)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR16(tt,ti,tj,tk,p,q,r,w,j) C2_NR16(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),((j)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR17(tt,ti,tj,tk,p,q,r,w,j) C2_NR17(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),((j)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR18(tt,ti,tj,tk,p,q,r,w,i,j) C2_NR18(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),((j)),(38 + 15*(tk) + (r) - (w))))
	#define SC2_NR19(tt,ti,tj,tk,p,q,r,w,k) C2_NR19(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),(15*(tj) + (q) + (w)),((k))))
	#define SC2_NR2(tt,ti,tj,tk,p,q,r,w) C2_NR2(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),(15*(tj) + (q) + (w)),(15*(tk) + (r) + (w))))
	#define SC2_NR20(tt,ti,tj,tk,p,q,r,w,k) C2_NR20(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),(15*(tj) + (q) + (w)),((k))))
	#define SC2_NR21(tt,ti,tj,tk,p,q,r,w,i,k) C2_NR21(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),(15*(tj) + (q) + (w)),((k))))
	#define SC2_NR22(tt,ti,tj,tk,p,q,r,w,k) C2_NR22(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),(38 + 15*(tj) + (q) - (w)),((k))))
	#define SC2_NR23(tt,ti,tj,tk,p,q,r,w,k) C2_NR23(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),(38 + 15*(tj) + (q) - (w)),((k))))
	#define SC2_NR24(tt,ti,tj,tk,p,q,r,w,i,k) C2_NR24(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),(38 + 15*(tj) + (q) - (w)),((k))))
	#define SC2_NR25(tt,ti,tj,tk,p,q,r,w,j,k) C2_NR25(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),((j)),((k))))
	#define SC2_NR26(tt,ti,tj,tk,p,q,r,w,j,k) C2_NR26(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),((j)),((k))))
	#define SC2_NR27(tt,ti,tj,tk,p,q,r,w,i,j,k) C2_NR27(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),((j)),((k))))
	#define SC2_NR3(tt,ti,tj,tk,p,q,r,w,i) C2_NR3(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),(15*(tj) + (q) + (w)),(15*(tk) + (r) + (w))))
	#define SC2_NR4(tt,ti,tj,tk,p,q,r,w) C2_NR4(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),(38 + 15*(tj) + (q) - (w)),(15*(tk) + (r) + (w))))
	#define SC2_NR5(tt,ti,tj,tk,p,q,r,w) C2_NR5(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),(38 + 15*(tj) + (q) - (w)),(15*(tk) + (r) + (w))))
	#define SC2_NR6(tt,ti,tj,tk,p,q,r,w,i) C2_NR6(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),(38 + 15*(tj) + (q) - (w)),(15*(tk) + (r) + (w))))
	#define SC2_NR7(tt,ti,tj,tk,p,q,r,w,j) C2_NR7(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(15*(ti) + (p) + (w)),((j)),(15*(tk) + (r) + (w))))
	#define SC2_NR8(tt,ti,tj,tk,p,q,r,w,j) C2_NR8(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),(38 + 15*(ti) + (p) - (w)),((j)),(15*(tk) + (r) + (w))))
	#define SC2_NR9(tt,ti,tj,tk,p,q,r,w,i,j) C2_NR9(tt,ti,tj,tk,p,q,r) += (WAll(((w)))) * (Y((12*(tt) - (w)),((i)),((j)),(15*(tk) + (r) + (w))))
	#define SC2_cb0(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR(tt,ti,tj,tk,p,q,r))
	#define SC2_cb1(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR2(tt,ti,tj,tk,p,q,r))
	#define SC2_cb10(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR11(tt,ti,tj,tk,p,q,r))
	#define SC2_cb11(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR12(tt,ti,tj,tk,p,q,r))
	#define SC2_cb12(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR13(tt,ti,tj,tk,p,q,r))
	#define SC2_cb13(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR14(tt,ti,tj,tk,p,q,r))
	#define SC2_cb14(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR15(tt,ti,tj,tk,p,q,r))
	#define SC2_cb15(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR16(tt,ti,tj,tk,p,q,r))
	#define SC2_cb16(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR17(tt,ti,tj,tk,p,q,r))
	#define SC2_cb17(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR18(tt,ti,tj,tk,p,q,r))
	#define SC2_cb18(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR19(tt,ti,tj,tk,p,q,r))
	#define SC2_cb19(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR20(tt,ti,tj,tk,p,q,r))
	#define SC2_cb2(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR3(tt,ti,tj,tk,p,q,r))
	#define SC2_cb20(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR21(tt,ti,tj,tk,p,q,r))
	#define SC2_cb21(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR22(tt,ti,tj,tk,p,q,r))
	#define SC2_cb22(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR23(tt,ti,tj,tk,p,q,r))
	#define SC2_cb23(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR24(tt,ti,tj,tk,p,q,r))
	#define SC2_cb24(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR25(tt,ti,tj,tk,p,q,r))
	#define SC2_cb25(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR26(tt,ti,tj,tk,p,q,r))
	#define SC2_cb26(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR27(tt,ti,tj,tk,p,q,r))
	#define SC2_cb3(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR4(tt,ti,tj,tk,p,q,r))
	#define SC2_cb4(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR5(tt,ti,tj,tk,p,q,r))
	#define SC2_cb5(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR6(tt,ti,tj,tk,p,q,r))
	#define SC2_cb6(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR7(tt,ti,tj,tk,p,q,r))
	#define SC2_cb7(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR8(tt,ti,tj,tk,p,q,r))
	#define SC2_cb8(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR9(tt,ti,tj,tk,p,q,r))
	#define SC2_cb9(tt,ti,tj,tk,p,q,r) C2(tt,ti,tj,tk,p,q,r) = (WCombos(((p)),((q)),((r)))) * (C2_NR10(tt,ti,tj,tk,p,q,r))
	#define SI(tt,ti,tj,tk) I(tt,ti,tj,tk) = ((I_NR(tt,ti,tj,tk)) - (C1(tt,ti,tj,tk))) / (C1(tt,ti,tj,tk))
	#define SI_NR(tt,ti,tj,tk,p,q,r) I_NR(tt,ti,tj,tk) += C2(tt,ti,tj,tk,p,q,r)
	#define SW(i,j,k) W(i,j,k) = ((((k) == (0)) && ((j) == (0))) && ((-1 + i) == (0))) ? (0.1249) : (((((k) == (0)) && ((1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((-1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1252) : (((((k) == (0)) && ((j) == (0))) && ((1 + i) == (0))) ? (0.1248) : (((((k) == (0)) && ((-1 + j) == (0))) && ((i) == (0))) ? (0.125) : (((((1 + k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.1251) : (((((k) == (0)) && ((j) == (0))) && ((i) == (0))) ? (0.25) : (0)))))))
	#define SWAll(w) WAll(w) = ((-1 + w) == (0)) ? (1) : ((WAll((-1 + (w)))) * (WCombos((0),(0),(0))))
	#define SWCombos(i,j,k,p,q,r) WCombos(i,j,k) += (WKernel(((i) - (p)),((j) - (q)),((k) - (r)))) * (W(((p)),((q)),((r))))
	#define SWKernel(i,j,k) WKernel(i,j,k) = (((((((1 + i) >= (0)) && ((1 - i) >= (0))) && ((1 + j) >= (0))) && ((1 - j) >= (0))) && ((1 + k) >= (0))) && ((1 - k) >= (0))) ? (1) : (0)
	#define SY_cb0(t,i,j,k) Y(t,i,j,k) = X(((i)),((j)),((k)))
	#define SY_cb1(t,i,j,k) Y(t,i,j,k) = Y((-1 + (t)),((i)),((j)),((k)))
	#define SY_cb2_hook(t,i,j,k) Y(t,i,j,k) = (((((((0.25) * (Y((-1 + (t)),((i)),((j)),((k))))) + ((0.1248) * (Y((-1 + (t)),(-1 + (i)),((j)),((k)))))) + ((0.1249) * (Y((-1 + (t)),(1 + (i)),((j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(-1 + (j)),((k)))))) + ((0.125) * (Y((-1 + (t)),((i)),(1 + (j)),((k)))))) + ((0.1251) * (Y((-1 + (t)),((i)),((j)),(-1 + (k)))))) + ((0.1252) * (Y((-1 + (t)),((i)),((j)),(1 + (k)))))
	#ifdef ERROR_INJECTION
	#define SY_cb2(t,i,j,k) do { SY_cb2_hook(t,i,j,k); if (t==12*(tt_INJ-1)+1 && i==15*ti_INJ+19 && j==15*tj_INJ+19 && k==15*tk_INJ+19) inject_star3d1r_abft_v2_12_15_15_15(&Y(t,i,j,k)); } while(0)
	#else
	#define SY_cb2(t,i,j,k) SY_cb2_hook(t,i,j,k)
	#endif

	// Timers
	double execution_time;
	initialize_timer();
	start_timer();

	/*
	 * domain: "[T, N] -> { SC2_cb25[tt, ti, tj, tk, p, q = 0, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2; SC2_NR16[tt, ti, tj, tk, p, q = 0, r, w, j] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < r <= 2 and 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w; SC2_cb1[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and -2 <= r < 0; SC2_cb24[tt, ti, tj, tk, p, q = 0, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0; SC2_cb21[tt, ti, tj, tk, p, q, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2; SC2_NR14[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and 0 < r <= 2 and 0 < w <= 12; SC2_cb23[tt, ti, tj, tk, p = 0, q, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2; SW[i, j, k] : T >= 10 and N >= 20 and -1 <= i <= 1 and -1 <= j <= 1 and -1 <= k <= 1; SC2_cb16[tt, ti, tj, tk, p, q = 0, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < r <= 2; SC2_NR15[tt, ti, tj, tk, p = 0, q, r, w, i] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and 0 < r <= 2 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w; SC2_NR24[tt, ti, tj, tk, p = 0, q, r = 0, w, i, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tk + w <= k <= 38 + 15tk - w; SC2_cb13[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and 0 < r <= 2; SC2_cb18[tt, ti, tj, tk, p, q, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0; SY_cb2[t, i, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 < i < N and 0 < j < N and 0 < k < N; SC2_cb4[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and -2 <= r < 0; SWAll[w] : T >= 10 and N >= 20 and 0 < w <= 12; SWKernel[i, j, k] : T >= 10 and N >= 20 and -2 <= i <= 2 and -2 <= j <= 2 and -2 <= k <= 2; SC2_NR9[tt, ti, tj, tk, p = 0, q = 0, r, w, i, j] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= r < 0 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tj + w <= j <= 38 + 15tj - w; SC2_cb0[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and -2 <= r < 0; SC2_cb20[tt, ti, tj, tk, p = 0, q, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0; SC2_cb11[tt, ti, tj, tk, p = 0, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and 0 < r <= 2; SI_NR[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p <= 2 and -2 <= q <= 2 and -2 <= r <= 2; SY_cb1[t, i, j, k = N] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = N, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = N, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SY_cb1[t, i, j, k = 0] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= j <= N; SY_cb1[t, i, j = 0, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= i <= N and 0 <= k <= N; SY_cb1[t, i = 0, j, k] : T >= 10 and N >= 20 and 2 <= t <= T and 0 <= j <= N and 0 <= k <= N; SC2_NR17[tt, ti, tj, tk, p, q = 0, r, w, j] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < r <= 2 and 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w; SC2_NR12[tt, ti, tj, tk, p = 0, q, r, w, i] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and 0 < r <= 2 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w; SC2_NR21[tt, ti, tj, tk, p = 0, q, r = 0, w, i, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tk + w <= k <= 38 + 15tk - w; SC2_NR13[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and 0 < r <= 2 and 0 < w <= 12; SC2_NR25[tt, ti, tj, tk, p, q = 0, r = 0, w, j, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w and 15tk + w <= k <= 38 + 15tk - w; SC2_cb22[tt, ti, tj, tk, p, q, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2; SC2_NR18[tt, ti, tj, tk, p = 0, q = 0, r, w, i, j] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < r <= 2 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w and 15tj + w <= j <= 38 + 15tj - w; SC2_NR23[tt, ti, tj, tk, p, q, r = 0, w, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w; SC2_NR27[tt, ti, tj, tk, p = 0, q = 0, r = 0, w = 12, i, j, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 12 + 15ti <= i <= 26 + 15ti and 12 + 15tj <= j <= 26 + 15tj and 12 + 15tk <= k <= 26 + 15tk; SC2_NR2[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and -2 <= r < 0 and 0 < w <= 12; SC2_NR4[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and -2 <= r < 0 and 0 < w <= 12; SWCombos[i, j, k, p, q, r] : T >= 10 and N >= 20 and -2 <= i <= 2 and -2 <= j <= 2 and -2 <= k <= 2 and p >= -2 + i and -1 <= p <= 1 and p <= 2 + i and q >= -2 + j and -1 <= q <= 1 and q <= 2 + j and r >= -2 + k and -1 <= r <= 1 and r <= 2 + k; SC2_cb2[tt, ti, tj, tk, p = 0, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and -2 <= r < 0; SC2_cb6[tt, ti, tj, tk, p, q = 0, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= r < 0; SC2_cb9[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and 0 < r <= 2; SC2_cb7[tt, ti, tj, tk, p, q = 0, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= r < 0; SC2_NR26[tt, ti, tj, tk, p, q = 0, r = 0, w, j, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w and 15tk + w <= k <= 38 + 15tk - w; SC2_cb15[tt, ti, tj, tk, p, q = 0, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < r <= 2; SC2_cb8[tt, ti, tj, tk, p = 0, q = 0, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= r < 0; SC2_cb3[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and -2 <= r < 0; SC2_NR10[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and 0 < r <= 2 and 0 < w <= 12; SC2_NR5[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and 0 < q <= 2 and -2 <= r < 0 and 0 < w <= 12; SC2_cb19[tt, ti, tj, tk, p, q, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0; SC2_cb17[tt, ti, tj, tk, p = 0, q = 0, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < r <= 2; SC2_NR11[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and 0 < r <= 2 and 0 < w <= 12; SC2_NR[tt, ti, tj, tk, p, q, r, w] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and -2 <= r < 0 and 0 < w <= 12; SC2_cb12[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and 0 < r <= 2; SC2_NR8[tt, ti, tj, tk, p, q = 0, r, w, j] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= r < 0 and 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w; SC2_NR7[tt, ti, tj, tk, p, q = 0, r, w, j] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= r < 0 and 0 < w <= 12 and 15tj + w <= j <= 38 + 15tj - w; SC1[tt, ti, tj, tk, i, j, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 15ti <= i <= 38 + 15ti and 15tj <= j <= 38 + 15tj and 15tk <= k <= 38 + 15tk; SC2_cb5[tt, ti, tj, tk, p = 0, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and -2 <= r < 0; SI[tt, ti, tj, tk] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N; SC2_cb10[tt, ti, tj, tk, p, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and 0 < r <= 2; SC2_NR22[tt, ti, tj, tk, p, q, r = 0, w, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and 0 < q <= 2 and 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w; SC2_NR3[tt, ti, tj, tk, p = 0, q, r, w, i] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= q < 0 and -2 <= r < 0 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w; SY_cb0[t, i, j, k] : T >= 10 and N >= 20 and 0 <= t <= 1 and 0 <= i <= N and 0 <= j <= N and 0 <= k <= N; SC2_cb26[tt, ti, tj, tk, p = 0, q = 0, r = 0] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N; SC2_NR19[tt, ti, tj, tk, p, q, r = 0, w, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and -2 <= p < 0 and -2 <= q < 0 and 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w; SC2_cb14[tt, ti, tj, tk, p = 0, q, r] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and 0 < r <= 2; SC2_NR6[tt, ti, tj, tk, p = 0, q, r, w, i] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < q <= 2 and -2 <= r < 0 and 0 < w <= 12 and 15ti + w <= i <= 38 + 15ti - w; SC2_NR20[tt, ti, tj, tk, p, q, r = 0, w, k] : tt >= 2 and 12tt <= -12 + T and ti > 0 and 15ti <= -40 + N and tj > 0 and 15tj <= -40 + N and tk > 0 and 15tk <= -40 + N and 0 < p <= 2 and -2 <= q < 0 and 0 < w <= 12 and 15tk + w <= k <= 38 + 15tk - w }"
	 * child:
	 *   sequence:
	 *   - filter: "{ SW[i, j, k] }"
	 *   - filter: "{ SWKernel[i, j, k] }"
	 *   - filter: "{ SWCombos[i, j, k, p, q, r] }"
	 *   - filter: "{ SWAll[w] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SWAll[w] -> [(w)] }]"
	 *   - filter: "{ SC2_cb5[tt, ti, tj, tk, p, q, r]; SC2_NR21[tt, ti, tj, tk, p, q, r, w, i, k]; SC2_cb26[tt, ti, tj, tk, p, q, r]; SC2_NR12[tt, ti, tj, tk, p, q, r, w, i]; SY_cb1[t, i, j, k]; SC2_cb0[tt, ti, tj, tk, p, q, r]; SC2_cb14[tt, ti, tj, tk, p, q, r]; SC2_NR7[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR6[tt, ti, tj, tk, p, q, r, w, i]; SC2_NR22[tt, ti, tj, tk, p, q, r, w, k]; SC2_cb19[tt, ti, tj, tk, p, q, r]; SC2_NR19[tt, ti, tj, tk, p, q, r, w, k]; SC2_cb4[tt, ti, tj, tk, p, q, r]; SC2_cb3[tt, ti, tj, tk, p, q, r]; SC2_cb6[tt, ti, tj, tk, p, q, r]; SC2_cb24[tt, ti, tj, tk, p, q, r]; SC2_NR2[tt, ti, tj, tk, p, q, r, w]; SC2_NR20[tt, ti, tj, tk, p, q, r, w, k]; SC2_cb8[tt, ti, tj, tk, p, q, r]; SC2_NR9[tt, ti, tj, tk, p, q, r, w, i, j]; SC2_NR18[tt, ti, tj, tk, p, q, r, w, i, j]; SC2_cb20[tt, ti, tj, tk, p, q, r]; SC2_cb15[tt, ti, tj, tk, p, q, r]; SC2_cb22[tt, ti, tj, tk, p, q, r]; SC2_NR11[tt, ti, tj, tk, p, q, r, w]; SY_cb2[t, i, j, k]; SC2_cb9[tt, ti, tj, tk, p, q, r]; SC2_cb23[tt, ti, tj, tk, p, q, r]; SC2_NR10[tt, ti, tj, tk, p, q, r, w]; SC2_NR13[tt, ti, tj, tk, p, q, r, w]; SC2_NR14[tt, ti, tj, tk, p, q, r, w]; SC2_cb12[tt, ti, tj, tk, p, q, r]; SC2_cb10[tt, ti, tj, tk, p, q, r]; SC2_cb2[tt, ti, tj, tk, p, q, r]; SI_NR[tt, ti, tj, tk, p, q, r]; SI[tt, ti, tj, tk]; SC2_NR17[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR16[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR27[tt, ti, tj, tk, p, q, r, w, i, j, k]; SC2_cb1[tt, ti, tj, tk, p, q, r]; SC2_NR15[tt, ti, tj, tk, p, q, r, w, i]; SC2_NR8[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR24[tt, ti, tj, tk, p, q, r, w, i, k]; SC2_NR5[tt, ti, tj, tk, p, q, r, w]; SC2_cb13[tt, ti, tj, tk, p, q, r]; SC2_cb16[tt, ti, tj, tk, p, q, r]; SC2_cb11[tt, ti, tj, tk, p, q, r]; SC2_cb25[tt, ti, tj, tk, p, q, r]; SY_cb0[t, i, j, k]; SC2_NR3[tt, ti, tj, tk, p, q, r, w, i]; SC2_NR4[tt, ti, tj, tk, p, q, r, w]; SC2_NR[tt, ti, tj, tk, p, q, r, w]; SC2_NR26[tt, ti, tj, tk, p, q, r, w, j, k]; SC2_NR23[tt, ti, tj, tk, p, q, r, w, k]; SC2_cb7[tt, ti, tj, tk, p, q, r]; SC2_cb21[tt, ti, tj, tk, p, q, r]; SC2_cb18[tt, ti, tj, tk, p, q, r]; SC2_cb17[tt, ti, tj, tk, p, q, r]; SC2_NR25[tt, ti, tj, tk, p, q, r, w, j, k]; SC1[tt, ti, tj, tk, i, j, k] }"
	 *     child:
	 *       schedule: "[T, N] -> [{ SC2_NR6[tt, ti, tj, tk, p, q, r, w, i] -> [(12tt - w)]; SC2_NR20[tt, ti, tj, tk, p, q, r, w, k] -> [(12tt - w)]; SC2_cb1[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb24[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb21[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR14[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_cb23[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb16[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR15[tt, ti, tj, tk, p, q, r, w, i] -> [(12tt - w)]; SC2_NR24[tt, ti, tj, tk, p, q, r, w, i, k] -> [(12tt - w)]; SC2_cb13[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb18[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SY_cb2[t, i, j, k] -> [(t)]; SC2_cb4[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR9[tt, ti, tj, tk, p, q, r, w, i, j] -> [(12tt - w)]; SC2_cb0[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb20[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb11[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SI_NR[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SY_cb1[t, i, j, k] -> [(t)]; SC2_NR17[tt, ti, tj, tk, p, q, r, w, j] -> [(12tt - w)]; SC2_NR12[tt, ti, tj, tk, p, q, r, w, i] -> [(12tt - w)]; SC2_NR21[tt, ti, tj, tk, p, q, r, w, i, k] -> [(12tt - w)]; SC2_NR13[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_cb22[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR25[tt, ti, tj, tk, p, q, r, w, j, k] -> [(12tt - w)]; SC2_NR18[tt, ti, tj, tk, p, q, r, w, i, j] -> [(12tt - w)]; SC2_NR23[tt, ti, tj, tk, p, q, r, w, k] -> [(12tt - w)]; SC2_NR27[tt, ti, tj, tk, p, q, r, w, i, j, k] -> [(12tt - w)]; SC2_NR2[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_NR4[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_cb2[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb6[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb9[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb7[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb15[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR26[tt, ti, tj, tk, p, q, r, w, j, k] -> [(12tt - w)]; SC2_cb8[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb3[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR10[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_NR5[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_cb19[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_NR11[tt, ti, tj, tk, p, q, r, w] -> [(12tt - w)]; SC2_cb17[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb12[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR8[tt, ti, tj, tk, p, q, r, w, j] -> [(12tt - w)]; SC2_NR7[tt, ti, tj, tk, p, q, r, w, j] -> [(12tt - w)]; SC1[tt, ti, tj, tk, i, j, k] -> [(12tt)]; SC2_cb5[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SI[tt, ti, tj, tk] -> [(12tt)]; SC2_cb10[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR22[tt, ti, tj, tk, p, q, r, w, k] -> [(12tt - w)]; SC2_NR3[tt, ti, tj, tk, p, q, r, w, i] -> [(12tt - w)]; SY_cb0[t, i, j, k] -> [(t)]; SC2_cb26[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR19[tt, ti, tj, tk, p, q, r, w, k] -> [(12tt - w)]; SC2_cb14[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_cb25[tt, ti, tj, tk, p, q, r] -> [(12tt)]; SC2_NR16[tt, ti, tj, tk, p, q, r, w, j] -> [(12tt - w)] }]"
	 *       child:
	 *         sequence:
	 *         - filter: "{ SY_cb1[t, i, j, k]; SY_cb0[t, i, j, k]; SY_cb2[t, i, j, k] }"
	 *         - filter: "{ SC2_NR13[tt, ti, tj, tk, p, q, r, w]; SC2_NR2[tt, ti, tj, tk, p, q, r, w]; SC2_NR15[tt, ti, tj, tk, p, q, r, w, i]; SC2_NR12[tt, ti, tj, tk, p, q, r, w, i]; SC2_NR8[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR9[tt, ti, tj, tk, p, q, r, w, i, j]; SC2_NR17[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR14[tt, ti, tj, tk, p, q, r, w]; SC2_NR25[tt, ti, tj, tk, p, q, r, w, j, k]; SC2_NR21[tt, ti, tj, tk, p, q, r, w, i, k]; SC2_NR22[tt, ti, tj, tk, p, q, r, w, k]; SC2_NR24[tt, ti, tj, tk, p, q, r, w, i, k]; SC2_NR26[tt, ti, tj, tk, p, q, r, w, j, k]; SC2_NR16[tt, ti, tj, tk, p, q, r, w, j]; SC2_NR23[tt, ti, tj, tk, p, q, r, w, k]; SC2_NR27[tt, ti, tj, tk, p, q, r, w, i, j, k]; SC2_NR3[tt, ti, tj, tk, p, q, r, w, i]; SC2_NR18[tt, ti, tj, tk, p, q, r, w, i, j]; SC2_NR4[tt, ti, tj, tk, p, q, r, w]; SC2_NR5[tt, ti, tj, tk, p, q, r, w]; SC2_NR11[tt, ti, tj, tk, p, q, r, w]; SC2_NR20[tt, ti, tj, tk, p, q, r, w, k]; SC2_NR10[tt, ti, tj, tk, p, q, r, w]; SC2_NR19[tt, ti, tj, tk, p, q, r, w, k]; SC2_NR[tt, ti, tj, tk, p, q, r, w]; SC2_NR7[tt, ti, tj, tk, p, q, r, w, j]; SC1[tt, ti, tj, tk, i, j, k]; SC2_NR6[tt, ti, tj, tk, p, q, r, w, i] }"
	 *         - filter: "{ SC2_cb18[tt, ti, tj, tk, p, q, r]; SC2_cb15[tt, ti, tj, tk, p, q, r]; SC2_cb0[tt, ti, tj, tk, p, q, r]; SC2_cb21[tt, ti, tj, tk, p, q, r]; SC2_cb25[tt, ti, tj, tk, p, q, r]; SC2_cb2[tt, ti, tj, tk, p, q, r]; SC2_cb24[tt, ti, tj, tk, p, q, r]; SC2_cb17[tt, ti, tj, tk, p, q, r]; SC2_cb1[tt, ti, tj, tk, p, q, r]; SC2_cb14[tt, ti, tj, tk, p, q, r]; SC2_cb5[tt, ti, tj, tk, p, q, r]; SC2_cb9[tt, ti, tj, tk, p, q, r]; SC2_cb16[tt, ti, tj, tk, p, q, r]; SC2_cb26[tt, ti, tj, tk, p, q, r]; SC2_cb12[tt, ti, tj, tk, p, q, r]; SC2_cb3[tt, ti, tj, tk, p, q, r]; SC2_cb6[tt, ti, tj, tk, p, q, r]; SC2_cb10[tt, ti, tj, tk, p, q, r]; SC2_cb8[tt, ti, tj, tk, p, q, r]; SC2_cb4[tt, ti, tj, tk, p, q, r]; SC2_cb11[tt, ti, tj, tk, p, q, r]; SC2_cb22[tt, ti, tj, tk, p, q, r]; SC2_cb20[tt, ti, tj, tk, p, q, r]; SC2_cb7[tt, ti, tj, tk, p, q, r]; SC2_cb23[tt, ti, tj, tk, p, q, r]; SC2_cb19[tt, ti, tj, tk, p, q, r]; SC2_cb13[tt, ti, tj, tk, p, q, r] }"
	 *         - filter: "{ SI_NR[tt, ti, tj, tk, p, q, r] }"
	 *         - filter: "{ SI[tt, ti, tj, tk] }"
	 */
	for (int c0 = -1; c0 <= 1; c0 += 1) {
	  for (int c1 = -1; c1 <= 1; c1 += 1) {
	    for (int c2 = -1; c2 <= 1; c2 += 1) {
	      SW(c0, c1, c2);
	    }
	  }
	}
	for (int c0 = -2; c0 <= 2; c0 += 1) {
	  for (int c1 = -2; c1 <= 2; c1 += 1) {
	    for (int c2 = -2; c2 <= 2; c2 += 1) {
	      SWKernel(c0, c1, c2);
	    }
	  }
	}
	for (int c0 = -2; c0 <= 2; c0 += 1) {
	  for (int c1 = -2; c1 <= 2; c1 += 1) {
	    for (int c2 = -2; c2 <= 2; c2 += 1) {
	      for (int c3 = max(-1, c0 - 2); c3 <= min(1, c0 + 2); c3 += 1) {
	        for (int c4 = max(-1, c1 - 2); c4 <= min(1, c1 + 2); c4 += 1) {
	          for (int c5 = max(-1, c2 - 2); c5 <= min(1, c2 + 2); c5 += 1) {
	            SWCombos(c0, c1, c2, c3, c4, c5);
	          }
	        }
	      }
	    }
	  }
	}
	for (int c0 = 1; c0 <= 12; c0 += 1) {
	  SWAll(c0);
	}
	for (int c0 = 0; c0 <= 1; c0 += 1) {
	  for (int c2 = 0; c2 <= N; c2 += 1) {
	    for (int c3 = 0; c3 <= N; c3 += 1) {
	      for (int c4 = 0; c4 <= N; c4 += 1) {
	        SY_cb0(c0, c2, c3, c4);
	      }
	    }
	  }
	}
	for (int c0 = 2; c0 <= T; c0 += 1) {
	  for (int c2 = 1; c2 < N; c2 += 1) {
	    for (int c3 = 1; c3 < N; c3 += 1) {
	      for (int c4 = 1; c4 < N; c4 += 1) {
	        SY_cb2(c0, c2, c3, c4);
	      }
	    }
	  }
	  for (int c2 = 0; c2 <= N; c2 += 1) {
	    for (int c3 = 0; c3 <= N; c3 += 1) {
	      if (c2 >= 1 && N >= c2 + 1 && c3 >= 1 && N >= c3 + 1) {
	        SY_cb1(c0, c2, c3, 0);
	      } else {
	        if (c2 >= 1 && N >= c2 + 1 && c3 == 0) {
	          for (int c4 = 0; c4 < N; c4 += 1) {
	            SY_cb1(c0, c2, 0, c4);
	          }
	        } else {
	          if (c2 == 0 && N >= c3 + 1) {
	            for (int c4 = 0; c4 < N; c4 += 1) {
	              SY_cb1(c0, 0, c3, c4);
	            }
	          } else {
	            if (c2 == N && N >= c3 + 1) {
	              for (int c4 = 0; c4 < N; c4 += 1) {
	                SY_cb1(c0, N, c3, c4);
	              }
	            } else {
	              for (int c4 = 0; c4 < N; c4 += 1) {
	                SY_cb1(c0, c2, N, c4);
	              }
	            }
	          }
	        }
	      }
	      SY_cb1(c0, c2, c3, N);
	    }
	  }
	  if (c0 >= 12 && (c0 % 12) + T >= c0 + 24) {
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_NR14((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = -2; c6 < 0; c6 += 1) {
	            for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	              for (int c10 = -(c0 % 12) + 15 * c4 + 12; c10 <= (c0 % 12) + 15 * c4 + 26; c10 += 1) {
	                SC2_NR21((c0 + 12) / 12, c2, c3, c4, 0, c6, 0, -(c0 % 12) + 12, c9, c10);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c4 + 12; c9 <= (c0 % 12) + 15 * c4 + 26; c9 += 1) {
	                SC2_NR23((c0 + 12) / 12, c2, c3, c4, c5, c6, 0, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_NR2((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = 1; c6 <= 2; c6 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	                SC2_NR6((c0 + 12) / 12, c2, c3, c4, 0, c6, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c3 + 12; c9 <= (c0 % 12) + 15 * c3 + 26; c9 += 1) {
	                SC2_NR7((c0 + 12) / 12, c2, c3, c4, c5, 0, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = -2; c6 < 0; c6 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	                SC2_NR12((c0 + 12) / 12, c2, c3, c4, 0, c6, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c3 + 12; c9 <= (c0 % 12) + 15 * c3 + 26; c9 += 1) {
	                SC2_NR17((c0 + 12) / 12, c2, c3, c4, c5, 0, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_NR((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = 1; c6 <= 2; c6 += 1) {
	            for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	              for (int c10 = -(c0 % 12) + 15 * c4 + 12; c10 <= (c0 % 12) + 15 * c4 + 26; c10 += 1) {
	                SC2_NR24((c0 + 12) / 12, c2, c3, c4, 0, c6, 0, -(c0 % 12) + 12, c9, c10);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_NR5((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c9 = -(c0 % 12) + 15 * c3 + 12; c9 <= (c0 % 12) + 15 * c3 + 26; c9 += 1) {
	              for (int c10 = -(c0 % 12) + 15 * c4 + 12; c10 <= (c0 % 12) + 15 * c4 + 26; c10 += 1) {
	                SC2_NR26((c0 + 12) / 12, c2, c3, c4, c5, 0, 0, -(c0 % 12) + 12, c9, c10);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = -2; c6 < 0; c6 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	                SC2_NR3((c0 + 12) / 12, c2, c3, c4, 0, c6, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c3 + 12; c9 <= (c0 % 12) + 15 * c3 + 26; c9 += 1) {
	                SC2_NR16((c0 + 12) / 12, c2, c3, c4, c5, 0, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_NR11((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_NR10((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c9 = -(c0 % 12) + 15 * c3 + 12; c9 <= (c0 % 12) + 15 * c3 + 26; c9 += 1) {
	              for (int c10 = -(c0 % 12) + 15 * c4 + 12; c10 <= (c0 % 12) + 15 * c4 + 26; c10 += 1) {
	                SC2_NR25((c0 + 12) / 12, c2, c3, c4, c5, 0, 0, -(c0 % 12) + 12, c9, c10);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c7 = 1; c7 <= 2; c7 += 1) {
	            for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	              for (int c10 = -(c0 % 12) + 15 * c3 + 12; c10 <= (c0 % 12) + 15 * c3 + 26; c10 += 1) {
	                SC2_NR18((c0 + 12) / 12, c2, c3, c4, 0, 0, c7, -(c0 % 12) + 12, c9, c10);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_NR4((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_NR13((c0 + 12) / 12, c2, c3, c4, c5, c6, c7, -(c0 % 12) + 12);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c3 + 12; c9 <= (c0 % 12) + 15 * c3 + 26; c9 += 1) {
	                SC2_NR8((c0 + 12) / 12, c2, c3, c4, c5, 0, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = 1; c6 <= 2; c6 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	                SC2_NR15((c0 + 12) / 12, c2, c3, c4, 0, c6, c7, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c4 + 12; c9 <= (c0 % 12) + 15 * c4 + 26; c9 += 1) {
	                SC2_NR20((c0 + 12) / 12, c2, c3, c4, c5, c6, 0, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c4 + 12; c9 <= (c0 % 12) + 15 * c4 + 26; c9 += 1) {
	                SC2_NR19((c0 + 12) / 12, c2, c3, c4, c5, c6, 0, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c9 = -(c0 % 12) + 15 * c4 + 12; c9 <= (c0 % 12) + 15 * c4 + 26; c9 += 1) {
	                SC2_NR22((c0 + 12) / 12, c2, c3, c4, c5, c6, 0, -(c0 % 12) + 12, c9);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c7 = -2; c7 < 0; c7 += 1) {
	            for (int c9 = -(c0 % 12) + 15 * c2 + 12; c9 <= (c0 % 12) + 15 * c2 + 26; c9 += 1) {
	              for (int c10 = -(c0 % 12) + 15 * c3 + 12; c10 <= (c0 % 12) + 15 * c3 + 26; c10 += 1) {
	                SC2_NR9((c0 + 12) / 12, c2, c3, c4, 0, 0, c7, -(c0 % 12) + 12, c9, c10);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  if (c0 >= 24 && T >= c0 + 12 && c0 % 12 == 0) {
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 15 * c2; c5 <= 15 * c2 + 38; c5 += 1) {
	            for (int c6 = 15 * c3; c6 <= 15 * c3 + 38; c6 += 1) {
	              for (int c7 = 15 * c4; c7 <= 15 * c4 + 38; c7 += 1) {
	                SC1(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  if (T >= c0 + 24 && c0 % 12 == 0) {
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c9 = 15 * c2 + 12; c9 <= 15 * c2 + 26; c9 += 1) {
	            for (int c10 = 15 * c3 + 12; c10 <= 15 * c3 + 26; c10 += 1) {
	              for (int c11 = 15 * c4 + 12; c11 <= 15 * c4 + 26; c11 += 1) {
	                SC2_NR27((c0 / 12) + 1, c2, c3, c4, 0, 0, 0, 12, c9, c10, c11);
	              }
	            }
	          }
	        }
	      }
	    }
	  }
	  if (c0 >= 24 && T >= c0 + 12 && c0 % 12 == 0) {
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              SC2_cb18(c0 / 12, c2, c3, c4, c5, c6, 0);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          SC2_cb26(c0 / 12, c2, c3, c4, 0, 0, 0);
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_cb9(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            SC2_cb25(c0 / 12, c2, c3, c4, c5, 0, 0);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              SC2_cb7(c0 / 12, c2, c3, c4, c5, 0, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              SC2_cb21(c0 / 12, c2, c3, c4, c5, c6, 0);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = -2; c6 < 0; c6 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              SC2_cb11(c0 / 12, c2, c3, c4, 0, c6, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              SC2_cb16(c0 / 12, c2, c3, c4, c5, 0, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = -2; c6 < 0; c6 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              SC2_cb2(c0 / 12, c2, c3, c4, 0, c6, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_cb1(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = 1; c6 <= 2; c6 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              SC2_cb5(c0 / 12, c2, c3, c4, 0, c6, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              SC2_cb22(c0 / 12, c2, c3, c4, c5, c6, 0);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = 1; c6 <= 2; c6 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              SC2_cb14(c0 / 12, c2, c3, c4, 0, c6, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_cb4(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c7 = -2; c7 < 0; c7 += 1) {
	              SC2_cb6(c0 / 12, c2, c3, c4, c5, 0, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              SC2_cb19(c0 / 12, c2, c3, c4, c5, c6, 0);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_cb10(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = 1; c6 <= 2; c6 += 1) {
	            SC2_cb23(c0 / 12, c2, c3, c4, 0, c6, 0);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c6 = -2; c6 < 0; c6 += 1) {
	            SC2_cb20(c0 / 12, c2, c3, c4, 0, c6, 0);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = -2; c6 < 0; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_cb0(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = -2; c7 < 0; c7 += 1) {
	                SC2_cb3(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c7 = 1; c7 <= 2; c7 += 1) {
	              SC2_cb15(c0 / 12, c2, c3, c4, c5, 0, c7);
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_cb12(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c7 = 1; c7 <= 2; c7 += 1) {
	            SC2_cb17(c0 / 12, c2, c3, c4, 0, 0, c7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 < 0; c5 += 1) {
	            SC2_cb24(c0 / 12, c2, c3, c4, c5, 0, 0);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = 1; c5 <= 2; c5 += 1) {
	            for (int c6 = 1; c6 <= 2; c6 += 1) {
	              for (int c7 = 1; c7 <= 2; c7 += 1) {
	                SC2_cb13(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c7 = -2; c7 < 0; c7 += 1) {
	            SC2_cb8(c0 / 12, c2, c3, c4, 0, 0, c7);
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          for (int c5 = -2; c5 <= 2; c5 += 1) {
	            for (int c6 = -2; c6 <= 2; c6 += 1) {
	              for (int c7 = -2; c7 <= 2; c7 += 1) {
	                SI_NR(c0 / 12, c2, c3, c4, c5, c6, c7);
	              }
	            }
	          }
	        }
	      }
	    }
	    for (int c2 = 1; c2 < (N + 5) / 15 - 2; c2 += 1) {
	      for (int c3 = 1; c3 < (N + 5) / 15 - 2; c3 += 1) {
	        for (int c4 = 1; c4 < (N + 5) / 15 - 2; c4 += 1) {
	          SI(c0 / 12, c2, c3, c4);
	        }
	      }
	    }
	  }
	}

	stop_timer();
	execution_time = elapsed_time();

	#undef SY
	#undef SW
	#undef SWKernel
	#undef SWCombos
	#undef SWAll
	#undef SC1
	#undef SC2
	#undef SI
	#undef SC2_NR
	#undef SC2_NR2
	#undef SC2_NR3
	#undef SC2_NR4
	#undef SC2_NR5
	#undef SC2_NR6
	#undef SC2_NR7
	#undef SC2_NR8
	#undef SC2_NR9
	#undef SC2_NR10
	#undef SC2_NR11
	#undef SC2_NR12
	#undef SC2_NR13
	#undef SC2_NR14
	#undef SC2_NR15
	#undef SC2_NR16
	#undef SC2_NR17
	#undef SC2_NR18
	#undef SC2_NR19
	#undef SC2_NR20
	#undef SC2_NR21
	#undef SC2_NR22
	#undef SC2_NR23
	#undef SC2_NR24
	#undef SC2_NR25
	#undef SC2_NR26
	#undef SC2_NR27
	#undef SI_NR

	#if defined TIMING
	struct Result result = new_result();
	result.result = execution_time;
	
	#elif defined ERROR_INJECTION
	// Count checksum difference above THRESHOLD
	struct INJ inj = { tt_INJ, ti_INJ, tj_INJ, tk_INJ };
	struct Result result = new_result();
	result.bit = BIT;
	result.inj = inj;
	result.noise = -1;
	
	const char* verbose = getenv("VERBOSE");
	
	#define print_SI(tt,ti,tj,tk) printf("v2_I(%d,%d,%d,%d) = %E\n",tt,ti,tj,tk, fabs(I(tt,ti,tj,tk)))
	#define acc_noise(tt,ti,tj,tk) result.noise = max(result.noise, fabs(I(tt,ti,tj,tk)))
	#define SI(tt,ti,tj,tk) do { if (verbose != NULL && fabs(I(tt,ti,tj,tk))>=threshold) print_SI(tt,ti,tj,tk); acc_noise(tt,ti,tj,tk); if (tt==tt_INJ && ti==ti_INJ && tj==tj_INJ && tk==tk_INJ) { if (fabs(I(tt,ti,tj,tk))>=threshold) {result.TP++;} else {result.FN++;} } else { if (fabs(I(tt,ti,tj,tk))>=threshold) {result.FP++;} else {result.TN++;} } } while(0)
	
	float threshold = 0;
	const char* env_threshold = getenv("THRESHOLD");
	if (env_threshold != NULL) {
		threshold = atof(env_threshold);
	}
	
	for (int tt = 2; tt < T / 12; tt += 1) {
	  for (int ti = 1; ti < (N + 5) / 15 - 2; ti += 1) {
	    for (int tj = 1; tj < (N + 5) / 15 - 2; tj += 1) {
	      for (int tk = 1; tk < (N + 5) / 15 - 2; tk += 1) {
	        SI(tt, ti, tj, tk);
	      }
	    }
	  }
	}
	
	{
		long N = result.FP + result.TN;
		long P = result.FN + result.TP;
		if (P != 0 && N != 0) {
			result.TPR = 100 * ((float)result.TP) / P;
			result.FPR = 100 * ((float)result.FP) / N;
			result.FNR = 100 * ((float)result.FN) / P;
		}
	}
	#undef SI
	
	#endif

	// Free local memory allocation
	 free(WAll);
	
	for (int i=0; i<(3); i++) {
		for (int j=0; j<(3); j++) {
			 free(W[i][j]);
		}
		free(W[i]);
	}
	free(W);
	
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				 free(I_NR[tt][ti][tj]);
			}
			free(I_NR[tt][ti]);
		}
		free(I_NR[tt]);
	}
	free(I_NR);
	
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				 free(I[tt][ti][tj]);
			}
			free(I[tt][ti]);
		}
		free(I[tt]);
	}
	free(I);
	
	for (int i=0; i<(5); i++) {
		for (int j=0; j<(5); j++) {
			 free(WKernel[i][j]);
		}
		free(WKernel[i]);
	}
	free(WKernel);
	
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				 free(C1[tt][ti][tj]);
			}
			free(C1[tt][ti]);
		}
		free(C1[tt]);
	}
	free(C1);
	
	for (int i=0; i<(5); i++) {
		for (int j=0; j<(5); j++) {
			 free(WCombos[i][j]);
		}
		free(WCombos[i]);
	}
	free(WCombos);
	
	for (int tt=0; tt<((-36 + T >= 0 && -55 + N >= 0) ? ((-2 + floord(T, 12))) : 0); tt++) {
		for (int ti=0; ti<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); ti++) {
			for (int tj=0; tj<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tj++) {
				for (int tk=0; tk<((-36 + T >= 0 && -55 + N >= 0) ? ((-3 + floord(5 + N, 15))) : 0); tk++) {
					for (int p=0; p<((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0); p++) {
						for (int q=0; q<((-36 + T >= 0 && -55 + N >= 0) ? (5) : 0); q++) {
							 free(C2[tt][ti][tj][tk][p][q]);
						}
						free(C2[tt][ti][tj][tk][p]);
					}
					free(C2[tt][ti][tj][tk]);
				}
				free(C2[tt][ti][tj]);
			}
			free(C2[tt][ti]);
		}
		free(C2[tt]);
	}
	free(C2);
	
	return result;
	#endif
}
