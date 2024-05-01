const std = @import("std");

// Although this function looks imperative, note that its job is to
// declaratively construct a build graph that will be executed by an external
// runner.
pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const c_flags: [][]const u8 = &.{ "-Wall", "-ffast-math", "-O3", "-Werror", "-Wno-unused-parameter", "-Wno-unused-variable", "-Wno-unused-function", "-Wno-unused-value", "-Wno-unused-label", "-Wno-unused-but-set-variable", "-Wno-unused-const-variable", "-Wno-unused-local-typedefs", "-Wno-unused-macros" };

    const lib = b.addSharedLibrary(.{
        .name = "libmatalgo",
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });

    lib.addCSourceFile(.{ .file = "src/matrix.c", .flags = c_flags });
    lib.addIncludePath(b.path("includes"));
    b.installArtifact(lib);

    const exe = b.addExecutable(.{
        .name = "matalgo",
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    exe.addCSourceFile(.{ .file = "src/main.c", .flags = c_flags });
    exe.linkSystemLibrary("m");
    exe.linkLibrary(lib);
    exe.addIncludePath(b.path("includes"));

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
