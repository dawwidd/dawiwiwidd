using RazorPagesMovie.Data;
using Microsoft.EntityFrameworkCore;

namespace RazorPagesMovie {
    public class Startup {
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddRazorPages();

            services.AddDbContext<RazorPagesMovieContext>(options =>
                options.UseSqlite(Configuration.GetConnectionString("RazorPagesMovieContext")));
        }
    }
}