for dt = [2.5, 2, 1.5, 1, 0.5]
    f = figure('visible','off');
    cmd = ['./ssprk3 ', num2str(dt)];
    status = system(cmd);
    if status ~= 0
        disp('You should be running this from the build directory. Are you?')
        return
    end
    t = load('time.txt');
    u = load('solution.txt');
    plot(t, u, '-*', 'DisplayName','u(t)');
    hold on;
    xlabel('t')
    ylabel('u(t)')
    legend;
    outfile = ['solution_', num2str( floor(dt*10)), '.png'];
    saveas(gcf,outfile);
    close all;
end
