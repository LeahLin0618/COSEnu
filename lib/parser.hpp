class Params
{
public:
    std::string SCHEME;

    // Simulation specific configs.
    int END_TIME = 0;
    int DUMP_EVERY = 0;
    int ANAL_EVERY = 0;

    // Grid specific configs.
    int nz = 0;
    int nvz = 0;
    int gz = 0;

    double z0 = 0.0;
    double z1 = 0.0;
    double v0;
    double v1;
    double CFL = 0.0;
    double pmo = 0.0;
    double omega = 0.0;
    double theta = 0.0;
    double mu = 1.0;

    //Analysis related
    int n_vsnap = 0;
    std::vector<double> vsnap_zlocs;
    int v_snap_interval;

    int n_zsnap = 0;
    std::vector<double> zsnap_vmodes;
    int z_snap_interval;

    bool is_scheme = false;
    bool is_nz = false;
    bool is_nvz = false;
    bool is_z0 = false;
    bool is_z1 = false;
    bool is_v0 = false;
    bool is_v1 = false;
    bool is_CFL = false;
    bool is_gz = false;
    bool is_END_TIME = false;
    bool is_ANAL_EVERY = false;
    bool is_pmo = false;
    bool is_omega = false;
    bool is_theta = false;
    bool is_mu = false;

    Params(std::string CONFIG_FILE);
    ~Params() {}
};

Params::Params(std::string CONFIG_FILE)
{
    std::string line;
    std::string key;
    std::string value;

    std::ifstream config;
    config.open(CONFIG_FILE.c_str(), std::ifstream::in);
    if (!config)
    {
        std::cout << "[ FAIL ]...Unable to open "
                  << CONFIG_FILE
                  << "exitting for now"
                  << std::endl;
        exit(0);
    }
    while (config)
    {
        std::getline(config, line);
        if (line.length() > 0)
        {
            int pos = line.find_first_of(":");
            std::string left = line.substr(0, pos);
            std::string right = line.substr(pos + 1);
            if (left.length() > 0)
            {
                key = left.substr(0, left.find_first_of(" "));
                value = right.substr(right.find_first_not_of(" "), right.find_first_of("\n"));
            }
            if (key == "scheme")
            {
                string_to_type(value, SCHEME);
                is_scheme = true;
            }
            else if (key == "nz")
            {
                string_to_type(value, nz);
                is_nz = true;
            }
            else if (key == "nvz")
            {
                string_to_type(value, nvz);
                is_nvz = true;
            }
            else if (key == "CFL")
            {
                string_to_type(value, CFL);
                is_CFL = true;
            }
            else if (key == "gz")
            {
                string_to_type(value, gz);
                is_gz = true;
            }
            else if (key == "z0")
            {
                string_to_type(value, z0);
                is_z0 = true;
            }
            else if (key == "z1")
            {
                string_to_type(value, z1);
                is_z1 = true;
            }
            else if (key == "v0")
            {
                string_to_type(value, v0);
                is_v0 = true;
            }
            else if (key == "v1")
            {
                string_to_type(value, v1);
                is_v1 = true;
            }
            else if (key == "END_TIME")
            {
                string_to_type(value, END_TIME);
                is_END_TIME = true;
            }
            else if (key == "ANAL_EVERY")
            {
                string_to_type(value, ANAL_EVERY);
                is_ANAL_EVERY = true;
            }
#ifdef VAC_OSC_ON
            else if (key == "pmo")
            {
                string_to_type(value, pmo);
                is_pmo = true;
            }
            else if (key == "omega")
            {
                string_to_type(value, omega);
                is_omega = true;
            }
            else if (key == "theta")
            {
                string_to_type(value, theta);
                is_theta = true;
            }
#endif
#ifdef COLL_OSC_ON
            else if (key == "mu")
            {
                string_to_type(value, mu);
                is_mu = true;
            }
#endif
            else if (key == "n_vsnap")
            {
                string_to_type(value, n_vsnap);
            }
            else if (key == "vsnap_zlocs")
            {
                cssl_to_vec(value, vsnap_zlocs);
            }
            else if (key == "n_zsnaps")
            {
                string_to_type(value, n_zsnap);
            }
            else if (key == "zsnap_vmodes")
            {
                cssl_to_vec(value, zsnap_vmodes);
            }
            else
            {
                std::cout << "Redundant or unknown key: " << key << std::endl;
                continue;
            }
        }
    }
    //----------------------------------------------------------

    if (!(is_scheme && is_nz && is_nvz && is_z0 && is_z1 && is_v0 && is_v1 && is_CFL && is_gz &&
          is_END_TIME && is_ANAL_EVERY))
    {
        std::cout << "[ FAIL ]...Incomplete config file" << std::endl
                  << "Exiting." << std::endl;
        exit(0);
    }

#ifdef VAC_OSC_ON
    if (!(is_pmo && is_omega && is_theta))
    {
        std::cout << "[ FAIL ]...Incomplete config file" << std::endl
                  << "Exiting." << std::endl;
        exit(0);
    }
#endif
#ifdef COLL_OSC_ON
    if (!(is_mu))
    {
        std::cout << "[ FAIL ]...Incomplete config file" << std::endl
                  << "Exiting." << std::endl;
        exit(0);
    }
#endif
}