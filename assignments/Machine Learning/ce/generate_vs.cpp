void generate_vs(vector<int> diff, vector<string> p, vector<int> help)
{
    for(int i=0;i<diff.size();i++)
    {
        if(help[i] == 0)
        {
            p[diff[i]] = S[0][diff[i]];
        }
        else
        {
            p[diff[i]] = "?";
        }
    }
    VS.push_back(p);
    return ;
}

void permutation(int sz, vector<int> diff, vector<string> p, vector<int> help)
{
    if(sz > 1)
    {
        help[diff.size() - sz] = 0;
        permutation(sz-1, diff, p, help);
        help[diff.size() - sz] = 1;
        permutation(sz-1, diff, p, help);
    }
    else if (sz == 1)
    {
        help[diff.size() - sz] = 0;
        generate_vs(diff, p, help);
        help[diff.size() - sz] = 1;
        generate_vs(diff, p, help);
    }
    else
    {
        VS.push_back(S[0]);
    }
    return;
}

void reduce_VS(int m)
{
    vector<int> deletion;
    for(int i=0;i<VS.size();i++)
    {
        deletion.push_back(0);
    }
    for(int i=0;i<VS.size();i++)
    {
        if(deletion[i] == 0)
        {
            for(int j=i+1;j<VS.size();j++)
            {
                int cnt = 0;
                for(int k=0;k<m;k++)
                {
                    if(VS[i][k].compare(VS[j][k]) == 0)
                        cnt++;
                }
                if (cnt == m)
                {
                    deletion[j] = 1;
                }
            }
        }
    }
    for(int i=VS.size()-1;i>=0;i--)
    {
        if(deletion[i] == 1)
            VS.erase(VS.begin() + i);
    }
    return;
}

void print_VS(int n, int m)
{
    if(S[0][0].compare("NULL") != 0)
    {
        for(int i=0;i<G_count;i++)
        {
            vector<int> diff;
            for(int j=0;j<m;j++)
            {
                if(G[i][j].compare(S[0][j]) != 0)
                    diff.push_back(j);
            }
            int sz = diff.size();
            vector <int> help;
            for(int l=0;l<sz;l++)
                help.push_back(0);
            permutation(sz, diff, G[i], help);
        }
        reduce_VS(m);
        cout<<"\nVersion Space:-\n";
        for(int i=0;i<VS.size();i++)
        {
            for(int j=0;j<m;j++)
            {
                cout<<VS[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    else
    {
        for(int i=0;i<G_count;i++)
        {
            VS.push_back(G[i]);
        }
        for(int i=0;i<m;i++)
        {
            vector <vector <string> > temp;
            for(int j=0;j<VS.size();j++)
            {
                int acnt = 0;
                for(int k=0;k<m;k++)
                {
                    if(VS[j][k].compare("?") == 0)
                        acnt++;
                }
                if(acnt == m-i)
                    temp.push_back(VS[j]);
            }
            //--------------------------------------------------------------------------------------------------
            for(int p=0;p<temp.size();p++)
            {
                vector<int> diff;
                for(int j=0;j<m;j++)
                {
                    if(temp[p][j].compare("?") == 0)
                        diff.push_back(j);
                }
                set<string>::iterator it;
                for(int q=0;q<diff.size();q++)
                {
                    vector<string> dumb;
                    for(int r=0;r<m;r++)
                    {
                        dumb.push_back(temp[p][r]);
                    }
                    for (it=preproc_data[diff[q]].begin();it!=preproc_data[diff[q]].end(); ++it)
                    {
                        string s1 = *it;
                        dumb[diff[q]] = s1;
                        VS.push_back(dumb);
                    }
                }
            }
            reduce_VS(m);
            //--------------------------------------------------------------------------------------------------
        }
        reduce_VS(m);
        cout<<"\nVersion Space:-\n";
        for(int i=0;i<VS.size();i++)
        {
            for(int j=0;j<m;j++)
            {
                cout<<VS[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
    return;
}
