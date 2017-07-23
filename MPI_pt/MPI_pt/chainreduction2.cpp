#include "stdafx.h"
#include "funcs.h"
#include "globals.h"
#include "Cclass.h"

void chainreduction2(vector<vector<edge>> &H, vector<int> weight, bool connected, int buf_size, int vector_size, int size)
{
	vector<int> V; // considered nodes
	for (int i = 0; i<mask.size(); i++) if (!mask[i]) V.push_back(i);
	vector<int> C = fchain(H, V);

	if (!C.empty()) {
		chrs++;
		for (int i = 0; i<C.size(); i++) if (!exis(V, C[i])) mask[C[i]] = false;

		if (!exis(C, 0)) {
			edge T;
			T.C.push_back(1);
			vector<int> Ch = C;
			vector<vector<edge>> G(H.size());
			for (int i = 0; i<H.size(); i++) G[i] = H[i];
			for (int i = 0; i<Ch.size() - 1; i++) T = T*G[Ch[i]][Ch[i + 1]];

			edge F1, F2;
			int F3 = 0;
			for (int i = 0; i<Ch.size() - 1; i++) if (!exis(V, Ch[i])) { // i=Ch.size() - 1 doesn't make anything
				edge L; // save power,simple, but lost P.C
				L.C.push_back(1);
				for (int j = 0; j<i; j++) L = L*G[Ch[j]][Ch[j + 1]];
				F1 = F1 + weight[Ch[i]] * (L - T); // here arise size=1 - edge
			}
			for (int i = 1; i<Ch.size(); i++) if (!exis(V, Ch[i])) { // i=0 doesn't make anything
				edge P;
				P.C.push_back(1);
				for (int j = i; j<Ch.size() - 1; j++) P = P*G[Ch[j]][Ch[j + 1]];
				F2 = F2 + weight[Ch[i]] * (P - T);
			}

			for (int i = 0; i<Ch.size(); i++) if (!exis(V, Ch[i])) F3 += weight[Ch[i]];

			for (int i = 1; i<Ch.size() - 1; i++) { // after this we get 2 nodes from chain, one of them can be pivote
				delnode(G, Ch[i]);
				for (int j = 0; j<Ch.size(); j++) if (Ch[i] < Ch[j]) Ch[j]--; // not forget about Ch
			}
			int x = Ch.front(), y = Ch.back(); // matter x<=>y

			vector<vector<edge>> G1(G.size());
			for (int i = 0; i<G.size(); i++) G1[i] = G[i]; // after reduction G changed
			bool connec = gconnected(G);
			vector<bool> visited1 = visited;
			if (!connec) cout << "Get unconnected in chainreduction1 " << endl;

			if (!F2.C.empty()) {
				renumerate(G, y, 1);  // s - node out of chain always 0, so t=1

				str Gp;
				Gp.G = G;
				Gp.F.push_back(F2);
				Gp.ex = connec;
				Gp.V = visited;
				send_control(Gp, buf_size, vector_size, size);
			} // R1y

			if (!F1.C.empty()) {
				visited = visited1;
				G.resize(G1.size());
				for (int i = 0; i<G1.size(); i++) G[i] = G1[i];
				renumerate(G, x, 1);

				str Gp;
				Gp.G = G;
				Gp.F.push_back(F1);
				Gp.ex = connec;
				Gp.V = visited;
				send_control(Gp, buf_size, vector_size, size);
			} // R1x

			G.resize(G1.size());
			for (int i = 0; i<G1.size(); i++) G[i] = G1[i];
			int xy = x;
			if (y < xy) xy--; // not forget
			contractedge(G, y, x); // x or y can't be s

			if (xy != 1) renumerate(G, xy, 1); // 0 can not be in Ch

			edge m;

			if (!connec) {
				visited = visited1;
				int component1_size = 0;
				for (int i = 0; i < visited.size(); i++) if (visited[i]) component1_size++;
				int component2_size = visited.size() - component1_size;

				if (component1_size != 1 && component2_size != 1) {
					decomp1++;
					cout << "Decomposition chainreduction1:" << component1_size << " & " << component2_size << endl;
					vector<vector<edge>> J(G1.size());
					for (int i = 0; i < G1.size(); i++) J[i] = G1[i];

					if ((visited[0] && visited[x]) || (!visited[0] && !visited[x])) renumerate(J, x, 1);
					else renumerate(J, y, 1);

					str Gp;
					Gp.G = J;
					Gp.F.push_back(F3*T);
					Gp.ex = connec;
					Gp.V = visited;
					send_control(Gp, buf_size, vector_size, size); // R1xy
				}
				else {
					str Gp;
					Gp.G = G;
					Gp.F.push_back(F3*T);
					Gp.ex = connected;
					Gp.V = visited;
					send_control(Gp, buf_size, vector_size, size); // R1xy
				}
			}
			else {
				str Gp;
				Gp.G = G;
				Gp.F.push_back(F3*T);
				Gp.ex = connected;
				Gp.V = visited;
				send_control(Gp, buf_size, vector_size, size); // R1xy
			}
		}
		else {
			vector<int> Ch = C;
			vector<int>::iterator it, r;
			for (it = Ch.begin(); it<Ch.end(); ++it) if (*it == 0) r = it;
			int q = r - Ch.begin(); // place of pivote node s=0 into vector Ch 

			edge T;
			T.C.push_back(1);
			vector<vector<edge>> G(H.size());
			for (int i = 0; i<H.size(); i++) G[i] = H[i];
			for (int i = 0; i<Ch.size() - 1; i++) T = T*G[Ch[i]][Ch[i + 1]];

			edge F1, F2;
			int F3 = 0;
			for (int i = 0; i<Ch.size(); i++) if (i != q && !exis(V, Ch[i])) {
				edge P; // save power,simple, but lost P.C
				P.C.push_back(1);
				if (i < q) for (int j = i; j<q; j++) P = P*G[Ch[j]][Ch[j + 1]];
				else for (int j = q; j<i; j++) P = P*G[Ch[j]][Ch[j + 1]];
				F1 = F1 + weight[Ch[i]] * P;
			}
			for (int i = 0; i<Ch.size(); i++) if (i != q && !exis(V, Ch[i])) {
				edge L;
				L.C.push_back(1);
				if (i < q) {
					for (int j = 0; j < i; j++) L = L*G[Ch[j]][Ch[j + 1]];
					for (int j = q; j<Ch.size() - 1; j++) L = L*G[Ch[j]][Ch[j + 1]];
				}
				else {
					for (int j = 0; j < q; j++) L = L*G[Ch[j]][Ch[j + 1]];
					for (int j = i; j<Ch.size() - 1; j++) L = L*G[Ch[j]][Ch[j + 1]];
				}
				F2 = F2 + weight[Ch[i]] * L;
			}

			for (int i = 0; i<Ch.size(); i++) if (!exis(V, Ch[i])) F3 += weight[Ch[i]];

			for (int i = 1; i<Ch.size() - 1; i++) {
				delnode(G, Ch[i]);
				for (int j = 0; j<Ch.size(); j++) if (Ch[i] < Ch[j]) Ch[j]--; // not forget about Ch
			}

			bool connec = gconnected(G);
			if (!connec) cout << "Get unconnected in chainreduction2 " << endl;

			int x = Ch.front(), y = Ch.back(); // doesn't matter x<=>y
			if (x != 0 && x != 1 && y != 0 && y != 1) {
				renumerate(G, x, 0);
				renumerate(G, y, 1);
			}
			if (x == 0 && y != 1) renumerate(G, y, 1);
			if (x == 1 && y != 0) renumerate(G, y, 0);
			if (y == 0 && x != 1) renumerate(G, x, 1);
			if (y == 1 && x != 0) renumerate(G, x, 0);
			
			sum = sum + F1;

			str Gp;
			Gp.G = G;
			Gp.F.push_back(F2 - F3*T);
			Gp.ex = connec;
			Gp.V = visited;
			send_control(Gp, buf_size, vector_size, size);
		}
		chainreduction2(H, weight, connected, buf_size, vector_size, size);
	}
}